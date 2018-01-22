#include <dcdr/messaging/FlatBuffersParcelSerializer.h>

#include <dcdr/messaging/WorkerConnectRequest.h>
#include <serialization/FlatBuffers.h>

using namespace Dcdr::Interconnect;

IParcel::SerializedParcel FlatBuffersParcelSerializer::serialize(const WorkerConnectRequest& parcel)
{
    flatbuffers::FlatBufferBuilder flatBuffersBuilder(1024);

    auto session = flatBuffersBuilder.CreateVector(parcel.get_session_id().data(), parcel.get_session_id().size());

    auto token = flatBuffersBuilder.CreateVector(parcel.get_token().data(), parcel.get_token().size());

    auto requestDataBuilder = DcdrFlatBuffers::ConnectRequestDataBuilder(flatBuffersBuilder);
    requestDataBuilder.add_token(token);
    auto requestDataFlatBuffer = requestDataBuilder.Finish();


    DcdrFlatBuffers::WorkerRequestBuilder requestBuilder(flatBuffersBuilder);
    requestBuilder.add_session(session);
    requestBuilder.add_data_type(DcdrFlatBuffers::WorkerRequestData_ConnectRequestData);
    requestBuilder.add_data(requestDataFlatBuffer.Union());

    auto requestFlatBuffer = requestBuilder.Finish();

    flatBuffersBuilder.Finish(requestFlatBuffer);

    return IParcel::SerializedParcel(
            flatBuffersBuilder.GetBufferPointer(),
            flatBuffersBuilder.GetBufferPointer() + flatBuffersBuilder.GetSize());
}
