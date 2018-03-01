#include "FlatBuffersWorkerResponseSerializer.h"

#include <dcdr/messaging/worker/WorkerResponses.h>
#include <dcdr/logging/Logger.h>

#include "FlatBuffersSerializerUtils.h"

using namespace Dcdr::Logging;
using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

namespace
{
    const size_t WORKER_RESPONSE_BUILDER_BUFFER_SIZE = 4096;

    template <class ResponseType, class ParcelGenerator>
    IParcel::SerializedParcel build_worker_response_parcel(ParcelGenerator&& parcelGenerator)
    {
        return SerializerUtils::build_parcel<DcdrFlatBuffers::WorkerResponse>(
                [parcelGenerator=std::forward<ParcelGenerator>(parcelGenerator)] (auto& flatBuffersBuilder)
                {
                    log_debug(std::string()
                                      .append("[Interconnect][FlatBuffers] Serializing parcel into ")
                                      .append(ResponseType::GetFullyQualifiedName())
                                      .append(" flatbuffer"));

                    flatbuffers::Offset<ResponseType> responseData = parcelGenerator(flatBuffersBuilder);

                    log_debug(std::string()
                                      .append("[Interconnect][FlatBuffers] Parcel was serialized to ")
                                      .append(ResponseType::GetFullyQualifiedName())
                                      .append(" flatbuffer"));

                    return DcdrFlatBuffers::CreateWorkerResponse(
                            flatBuffersBuilder,
                            DcdrFlatBuffers::WorkerResponseDataTraits<ResponseType>::enum_value,
                            responseData.Union());
                },
                WORKER_RESPONSE_BUILDER_BUFFER_SIZE);
    }
}

IParcel::SerializedParcel FlatBuffersWorkerResponseSerizlizer::serialize(const WorkerServerStatusResponse &parcel)
{
    return build_worker_response_parcel<DcdrFlatBuffers::WorkerServerStatusResponse>(
            [&parcel](flatbuffers::FlatBufferBuilder& builder) {
                return DcdrFlatBuffers::CreateWorkerServerStatusResponse(
                        builder,
                        parcel.get_node_id(),
                        SerializerUtils::marshal(parcel.get_status()),
                        builder.CreateString(parcel.get_message()));
            });
}

IParcel::SerializedParcel FlatBuffersWorkerResponseSerizlizer::serialize(const WorkerLoginResponse &parcel)
{
    return build_worker_response_parcel<DcdrFlatBuffers::WorkerLoginResponse>(
            [&parcel](flatbuffers::FlatBufferBuilder& builder) {
                return DcdrFlatBuffers::CreateWorkerLoginResponse(
                        builder,
                        parcel.get_node_id());
            });
}

IParcel::SerializedParcel FlatBuffersWorkerResponseSerizlizer::serialize(const WorkerPollTasksResponse &parcel)
{
    return build_worker_response_parcel<DcdrFlatBuffers::WorkerPollTasksResponse>(
            [&parcel](flatbuffers::FlatBufferBuilder& builder) {
                return DcdrFlatBuffers::CreateWorkerPollTasksResponse(
                        builder,
                        parcel.get_node_id(),
                        SerializerUtils::serialize_vector<Worker::TaskInfo, DcdrFlatBuffers::TaskInfo>(
                                builder, parcel.get_tasks()));
            });
}

IParcel::SerializedParcel FlatBuffersWorkerResponseSerizlizer::serialize(const WorkerDownloadSceneResponse &parcel)
{
    return build_worker_response_parcel<DcdrFlatBuffers::WorkerDownloadSceneResponse>(
            [&parcel](flatbuffers::FlatBufferBuilder& builder) {
                return DcdrFlatBuffers::CreateWorkerDownloadSceneResponse(
                        builder,
                        parcel.get_node_id(),
                        parcel.get_scene_id(),
                        parcel.get_offset(),
                        parcel.get_bytes_left(),
                        builder.CreateVector<uint8_t>(parcel.get_data()));
            });
}
