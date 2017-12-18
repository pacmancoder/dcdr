#include <dcdr/messaging/FlatBuffersRequestDeserializer.h>

#include <serialization/FlatBuffers.h>
#include <dcdr/messaging/ConnectRequest.h>
#include <dcdr/messaging/ServerConnection.h>

using namespace Dcdr::Interconnect;

namespace
{
    FlatBuffersRequestDeserializer::IRequestPtr deserialize_connect_request(
            const DcdrFlatBuffers::ConnectRequestData* data)
    {
        auto userToken = std::string(data->userToken()->c_str());
        return FlatBuffersRequestDeserializer::IRequestPtr(new ConnectRequest(userToken));
    }
}

void FlatBuffersRequestDeserializer::deserialize(const std::vector<uint8_t>& buffer)
{
    connection_.clear();
    request_.reset(nullptr);

    auto requestFlatBuffer = flatbuffers::GetRoot<DcdrFlatBuffers::Request>(buffer.data());
    switch (requestFlatBuffer->requestData_type())
    {
        case DcdrFlatBuffers::RequestData_ConnectRequestData:
        {
            request_ = deserialize_connect_request(requestFlatBuffer->requestData_as_ConnectRequestData());
            break;
        }
        default:
            break;
    }
}

IRequestDeserializer::IRequestPtr FlatBuffersRequestDeserializer::get_request() {
    return std::move(request_);
}

std::string FlatBuffersRequestDeserializer::get_connection() {
    return connection_;
}
