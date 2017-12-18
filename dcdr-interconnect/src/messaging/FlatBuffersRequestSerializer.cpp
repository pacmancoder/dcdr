#include <dcdr/messaging/FlatBuffersRequestSerializer.h>

#include <dcdr/messaging/IRequest.h>
#include <dcdr/messaging/ConnectRequest.h>

#include <serialization/FlatBuffers.h>

using namespace Dcdr::Interconnect;

void FlatBuffersRequestSerializer::set_request(IRequestSerializer::IRequestPtr request)
{
    request_ = std::move(request);
}

void FlatBuffersRequestSerializer::set_connection(const std::string& connection)
{
    connection_ = connection;
}

std::vector<uint8_t> FlatBuffersRequestSerializer::serialize()
{
    return request_->serialize(*this);
}

std::vector<uint8_t> FlatBuffersRequestSerializer::serialize(const ConnectRequest &request) {
    flatbuffers::FlatBufferBuilder flatBuffersBuilder(1024);

    auto userToken = flatBuffersBuilder.CreateString(request.get_user_token());

    auto requestDataBuilder = DcdrFlatBuffers::ConnectRequestDataBuilder(flatBuffersBuilder);
    requestDataBuilder.add_userToken(userToken);
    auto requestDataFlatBuffer = requestDataBuilder.Finish();

    DcdrFlatBuffers::RequestBuilder requestBuilder(flatBuffersBuilder);
    requestBuilder.add_requestData_type(DcdrFlatBuffers::RequestData_ConnectRequestData);
    requestBuilder.add_requestData(requestDataFlatBuffer.Union());
    auto requestFlatBuffer = requestBuilder.Finish();

    flatBuffersBuilder.Finish(requestFlatBuffer);

    return std::vector<uint8_t>(
            flatBuffersBuilder.GetBufferPointer(),
            flatBuffersBuilder.GetBufferPointer() + flatBuffersBuilder.GetSize());
}
