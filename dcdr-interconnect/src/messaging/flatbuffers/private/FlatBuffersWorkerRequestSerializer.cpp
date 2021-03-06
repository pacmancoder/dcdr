#include "FlatBuffersWorkerRequestSerializer.h"

#include <dcdr/logging/Logger.h>
#include <dcdr/messaging/worker/WorkerRequests.h>

#include "FlatBuffersSerializerUtils.h"

using namespace Dcdr::Logging;
using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

namespace
{
    const char* LOG_PREFIX = "[Interconnect][FlatBuffers] ";
    const size_t WORKER_REQUEST_BUILDER_BUFFER_SIZE = 1024 * 128;

    template <class RequestType, class ParcelGenerator>
    IParcel::SerializedParcel build_worker_request_parcel(ParcelGenerator&& parcelGenerator)
    {
        return SerializerUtils::build_parcel<DcdrFlatBuffers::WorkerRequest>(
                [parcelGenerator=std::forward<ParcelGenerator>(parcelGenerator)] (auto& flatBuffersBuilder)
                {
                    log_trace(LOG_PREFIX, "Serializing parcel into ", RequestType::GetFullyQualifiedName());

                    flatbuffers::Offset<RequestType> requestData = parcelGenerator(flatBuffersBuilder);

                    log_trace(LOG_PREFIX, "Parcel was serialized to ", RequestType::GetFullyQualifiedName());

                    return DcdrFlatBuffers::CreateWorkerRequest(
                            flatBuffersBuilder,
                            DcdrFlatBuffers::WorkerRequestDataTraits<RequestType>::enum_value,
                            requestData.Union());
                },
                WORKER_REQUEST_BUILDER_BUFFER_SIZE);
    }
}

IParcel::SerializedParcel FlatBuffersWorkerRequestSerializer::serialize(const WorkerLoginRequest& parcel)
{
    return build_worker_request_parcel<DcdrFlatBuffers::WorkerLoginRequest>(
        [&parcel](flatbuffers::FlatBufferBuilder& builder)
        {
            return DcdrFlatBuffers::CreateWorkerLoginRequest(
                    builder,
                    parcel.get_node_id(),
                    builder.CreateString(parcel.get_name()),
                    builder.CreateString(parcel.get_token()));
        });
}

IParcel::SerializedParcel FlatBuffersWorkerRequestSerializer::serialize(const WorkerLogoutRequest& parcel)
{
    return build_worker_request_parcel<DcdrFlatBuffers::WorkerLogoutRequest>(
            [&parcel](flatbuffers::FlatBufferBuilder& builder)
            {
                return DcdrFlatBuffers::CreateWorkerLogoutRequest(builder, parcel.get_node_id());
            });
}

IParcel::SerializedParcel FlatBuffersWorkerRequestSerializer::serialize(const WorkerSendHardwareInfoRequest& parcel)
{
    return build_worker_request_parcel<DcdrFlatBuffers::WorkerSendHardwareInfoRequest>(
            [&parcel](flatbuffers::FlatBufferBuilder& builder)
            {
                return DcdrFlatBuffers::CreateWorkerSendHardwareInfoRequest(
                        builder,
                        parcel.get_node_id(),
                        SerializerUtils::serialize_vector<PropertyPair, DcdrFlatBuffers::PropertyPair>(
                                builder, parcel.get_properties()));
            });
}

IParcel::SerializedParcel FlatBuffersWorkerRequestSerializer::serialize(const WorkerPollTasksRequest& parcel)
{
    return build_worker_request_parcel<DcdrFlatBuffers::WorkerPollTasksRequest>(
            [&parcel](flatbuffers::FlatBufferBuilder& builder)
            {
                return DcdrFlatBuffers::CreateWorkerPollTasksRequest(builder, parcel.get_node_id());
            });
}

IParcel::SerializedParcel FlatBuffersWorkerRequestSerializer::serialize(const WorkerCommitTasksRequest& parcel)
{
    return build_worker_request_parcel<DcdrFlatBuffers::WorkerCommitTasksRequest>(
            [&parcel](flatbuffers::FlatBufferBuilder& builder)
            {
                return DcdrFlatBuffers::CreateWorkerCommitTasksRequest(
                        builder,
                        parcel.get_node_id(),
                        SerializerUtils::serialize_vector<Worker::TaskArtifact, DcdrFlatBuffers::TaskArtifact>(
                                builder, parcel.get_artifacts()));
            });
}

IParcel::SerializedParcel FlatBuffersWorkerRequestSerializer::serialize(const WorkerDownloadSceneRequest& parcel)
{
    return build_worker_request_parcel<DcdrFlatBuffers::WorkerDownloadSceneRequest>(
            [&parcel](flatbuffers::FlatBufferBuilder& builder)
            {
                return DcdrFlatBuffers::CreateWorkerDownloadSceneRequest(
                        builder,
                        parcel.get_node_id(),
                        parcel.get_scene_id(),
                        parcel.get_offset());
            });
}

IParcel::SerializedParcel FlatBuffersWorkerRequestSerializer::serialize(const WorkerGetSceneInfoRequest &parcel)
{
    return build_worker_request_parcel<DcdrFlatBuffers::WorkerGetSceneInfoRequest>(
            [&parcel](flatbuffers::FlatBufferBuilder& builder)
            {
                return DcdrFlatBuffers::CreateWorkerGetSceneInfoRequest(
                        builder, parcel.get_node_id(), parcel.get_scene_id());
            });
}
