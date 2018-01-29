#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>

#include <dcdr/logging/Logger.h>
#include <dcdr/messaging/worker/WorkerConnectRequest.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceInfoResponse.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceInfoRequest.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceResponse.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceRequest.h>

#include <flatbuffers-generated/DcdrFlatBuffers.h>

#include <vector>
#include <iostream>

using namespace Dcdr::Logging;
using namespace Dcdr::Interconnect;

namespace
{
    template <class T>
    IParcel::SerializedParcel flatbuffer_to_serialized_parcel(
            flatbuffers::FlatBufferBuilder& flatBuffersBuilder,
            flatbuffers::Offset<T> parcel)
    {
        auto parcelBuilder = DcdrFlatBuffers::ParcelBuilder(flatBuffersBuilder);
        parcelBuilder.add_parcelData_type(DcdrFlatBuffers::ParcelDataTraits<T>::enum_value);
        parcelBuilder.add_parcelData(parcel.Union());
        auto parcelFlatBuffer = parcelBuilder.Finish();

        flatBuffersBuilder.Finish(parcelFlatBuffer);

        return IParcel::SerializedParcel(
                flatBuffersBuilder.GetBufferPointer(),
                flatBuffersBuilder.GetBufferPointer() + flatBuffersBuilder.GetSize());
    }

    const size_t DEFAULT_FLATBUFFER_BUILDER_SIZE = 1024;
}

IParcel::SerializedParcel FlatBuffersParcelSerializer::serialize(const WorkerConnectRequest& parcel)
{
    flatbuffers::FlatBufferBuilder flatBuffersBuilder(DEFAULT_FLATBUFFER_BUILDER_SIZE);

    auto session = flatBuffersBuilder.CreateVector(parcel.get_session_id().data(), parcel.get_session_id().size());

    auto token = flatBuffersBuilder.CreateVector(parcel.get_token().data(), parcel.get_token().size());

    auto requestDataBuilder = DcdrFlatBuffers::WorkerConnectRequestBuilder(flatBuffersBuilder);
    requestDataBuilder.add_token(token);
    auto requestDataFlatBuffer = requestDataBuilder.Finish();


    DcdrFlatBuffers::WorkerRequestBuilder requestBuilder(flatBuffersBuilder);
    requestBuilder.add_session(session);
    requestBuilder.add_requestData_type(DcdrFlatBuffers::WorkerRequestData_WorkerConnectRequest);
    requestBuilder.add_requestData(requestDataFlatBuffer.Union());

    log_debug("[Interconnect][FlatBuffers] WorkerConnectRequest parcel was serialized");
    return flatbuffer_to_serialized_parcel(flatBuffersBuilder, requestBuilder.Finish());
}

IParcel::SerializedParcel FlatBuffersParcelSerializer::serialize(const CommanderGetSurfaceInfoRequest&)
{
    flatbuffers::FlatBufferBuilder flatBuffersBuilder(DEFAULT_FLATBUFFER_BUILDER_SIZE);

    auto requestDataBuilder = DcdrFlatBuffers::CommanderGetSurfaceInfoRequestBuilder(flatBuffersBuilder);
    auto requestDataFlatBuffer = requestDataBuilder.Finish();

    DcdrFlatBuffers::CommanderRequestBuilder requestBuilder(flatBuffersBuilder);
    requestBuilder.add_requestData_type(DcdrFlatBuffers::CommanderRequestData_CommanderGetSurfaceInfoRequest);
    requestBuilder.add_requestData(requestDataFlatBuffer.Union());

    log_debug("[Interconnect][FlatBuffers] CommanderGetSurfaceInfoRequest parcel was serialized");
    return flatbuffer_to_serialized_parcel(flatBuffersBuilder, requestBuilder.Finish());
}

IParcel::SerializedParcel FlatBuffersParcelSerializer::serialize(const CommanderGetSurfaceRequest&)
{
    flatbuffers::FlatBufferBuilder flatBuffersBuilder(DEFAULT_FLATBUFFER_BUILDER_SIZE);

    auto requestDataBuilder = DcdrFlatBuffers::CommanderGetSurfaceRequestBuilder(flatBuffersBuilder);
    auto requestDataFlatBuffer = requestDataBuilder.Finish();

    DcdrFlatBuffers::CommanderRequestBuilder requestBuilder(flatBuffersBuilder);
    requestBuilder.add_requestData_type(DcdrFlatBuffers::CommanderRequestData_CommanderGetSurfaceRequest);
    requestBuilder.add_requestData(requestDataFlatBuffer.Union());

    log_debug("[Interconnect][FlatBuffers] CommanderGetSurfaceRequest parcel was serialized");
    return flatbuffer_to_serialized_parcel(flatBuffersBuilder, requestBuilder.Finish());
}

IParcel::SerializedParcel FlatBuffersParcelSerializer::serialize(const CommanderGetSurfaceInfoResponse& parcel)
{
    flatbuffers::FlatBufferBuilder flatBuffersBuilder(DEFAULT_FLATBUFFER_BUILDER_SIZE);

    auto responseDataBuilder = DcdrFlatBuffers::CommanderGetSurfaceInfoResponseBuilder(flatBuffersBuilder);
    responseDataBuilder.add_width(parcel.get_width());
    responseDataBuilder.add_height(parcel.get_height());
    auto responseDataFlatBuffer = responseDataBuilder.Finish();

    DcdrFlatBuffers::CommanderResponseBuilder responseBuilder(flatBuffersBuilder);
    responseBuilder.add_responseData_type(DcdrFlatBuffers::CommanderResponseData_CommanderGetSurfaceInfoResponse);
    responseBuilder.add_responseData(responseDataFlatBuffer.Union());

    log_debug("[Interconnect][FlatBuffers] CommanderGetSurfaceInfoResponse parcel was serialized");
    return flatbuffer_to_serialized_parcel(flatBuffersBuilder, responseBuilder.Finish());
}

IParcel::SerializedParcel FlatBuffersParcelSerializer::serialize(const CommanderGetSurfaceResponse& parcel)
{
    flatbuffers::FlatBufferBuilder flatBuffersBuilder(DEFAULT_FLATBUFFER_BUILDER_SIZE);

    auto imageBuffer = flatBuffersBuilder.CreateVector(parcel.get_image_buffer());

    auto responseDataBuilder = DcdrFlatBuffers::CommanderGetSurfaceResponseBuilder(flatBuffersBuilder);
    responseDataBuilder.add_format(static_cast<DcdrFlatBuffers::SurfaceImageFormat>(parcel.get_image_format()));
    responseDataBuilder.add_buffer(imageBuffer);
    auto responseDataFlatBuffer = responseDataBuilder.Finish();

    DcdrFlatBuffers::CommanderResponseBuilder responseBuilder(flatBuffersBuilder);
    responseBuilder.add_responseData_type(DcdrFlatBuffers::CommanderResponseData_CommanderGetSurfaceResponse);
    responseBuilder.add_responseData(responseDataFlatBuffer.Union());

    log_debug("[Interconnect][FlatBuffers] CommanderGetSurfaceResponse parcel was serialized");
    return flatbuffer_to_serialized_parcel(flatBuffersBuilder, responseBuilder.Finish());
}
