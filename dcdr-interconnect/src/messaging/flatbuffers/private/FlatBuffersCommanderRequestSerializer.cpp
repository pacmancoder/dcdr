#include "FlatBuffersCommanderRequestSerializer.h"

#include <dcdr/logging/Logger.h>
#include <dcdr/messaging/commander/CommanderRequests.h>

#include <iostream>
#include <stdexcept>

#include "FlatBuffersSerializerUtils.h"


using namespace Dcdr::Logging;
using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

namespace
{
    const size_t COMMANDER_REQUEST_BUILDER_BUFFER_SIZE = 128;

    template <class RequestType, class ParcelGenerator>
    IParcel::SerializedParcel build_commander_request_parcel(ParcelGenerator&& parcelGenerator)
    {
        return SerializerUtils::build_parcel<DcdrFlatBuffers::CommanderRequest>(
            [parcelGenerator=std::forward<ParcelGenerator>(parcelGenerator)] (auto& flatBuffersBuilder)
            {
                log_debug(std::string()
                    .append("[Interconnect][FlatBuffers] Serializing parcel into ")
                    .append(RequestType::GetFullyQualifiedName())
                    .append(" flatbuffer"));

                flatbuffers::Offset<RequestType> requestData = parcelGenerator(flatBuffersBuilder);

                log_debug(std::string()
                                  .append("[Interconnect][FlatBuffers] Parcel was serialized to ")
                                  .append(RequestType::GetFullyQualifiedName())
                                  .append(" flatbuffer"));

                return DcdrFlatBuffers::CreateCommanderRequest(
                        flatBuffersBuilder,
                        DcdrFlatBuffers::CommanderRequestDataTraits<RequestType>::enum_value,
                        requestData.Union());
            },
            COMMANDER_REQUEST_BUILDER_BUFFER_SIZE);
    }
}

IParcel::SerializedParcel FlatBuffersCommanderRequestSerializer::serialize(const CommanderGetJobListRequest& parcel)
{
    return build_commander_request_parcel<DcdrFlatBuffers::CommanderGetJobListRequest>(
        [&parcel](auto& flatBuffersBuilder)
        {
            return DcdrFlatBuffers::CreateCommanderGetJobListRequest(
                    flatBuffersBuilder);
        });
}

IParcel::SerializedParcel FlatBuffersCommanderRequestSerializer::serialize(const CommanderGetJobInfoRequest& parcel)
{
    return build_commander_request_parcel<DcdrFlatBuffers::CommanderGetJobInfoRequest>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetJobInfoRequest(
                        flatBuffersBuilder,
                        parcel.get_job_id());
            });
}

IParcel::SerializedParcel FlatBuffersCommanderRequestSerializer::serialize(const CommanderGetJobArtifactRequest& parcel)
{
    return build_commander_request_parcel<DcdrFlatBuffers::CommanderGetJobArtifactRequest>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetJobArtifactRequest(
                        flatBuffersBuilder,
                        parcel.get_job_id(),
                        SerializerUtils::marshal(parcel.get_format()),
                        parcel.get_mipmap_level());
            });
}

IParcel::SerializedParcel FlatBuffersCommanderRequestSerializer::serialize(const CommanderSetJobStateRequest& parcel)
{
    return build_commander_request_parcel<DcdrFlatBuffers::CommanderSetJobStateRequest>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderSetJobStateRequest(
                        flatBuffersBuilder,
                        parcel.get_job_id(),
                        SerializerUtils::marshal(parcel.get_job_state()));
            });
}

IParcel::SerializedParcel FlatBuffersCommanderRequestSerializer::serialize(const CommanderAddJobRequest& parcel)
{
    return build_commander_request_parcel<DcdrFlatBuffers::CommanderAddJobRequest>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderAddJobRequest(
                        flatBuffersBuilder,
                        parcel.get_scene_id(),
                        parcel.get_scale());
            });
}

IParcel::SerializedParcel FlatBuffersCommanderRequestSerializer::serialize(const CommanderGetSceneListRequest& parcel)
{
    return build_commander_request_parcel<DcdrFlatBuffers::CommanderGetSceneListRequest>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetSceneListRequest(
                        flatBuffersBuilder);
            });
}

IParcel::SerializedParcel FlatBuffersCommanderRequestSerializer::serialize(const CommanderGetNodeListRequest& parcel)
{
    return build_commander_request_parcel<DcdrFlatBuffers::CommanderGetNodeListRequest>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetNodeListRequest(
                        flatBuffersBuilder);
            });
}

IParcel::SerializedParcel FlatBuffersCommanderRequestSerializer::serialize(const CommanderGetNodeInfoRequest& parcel)
{
    return build_commander_request_parcel<DcdrFlatBuffers::CommanderGetNodeInfoRequest>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetNodeInfoRequest(
                        flatBuffersBuilder,
                        parcel.get_node_id());
            });
}

IParcel::SerializedParcel FlatBuffersCommanderRequestSerializer::serialize(const CommanderSetNodeStateRequest& parcel)
{
    return build_commander_request_parcel<DcdrFlatBuffers::CommanderSetNodeStateRequest>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderSetNodeStateRequest(
                        flatBuffersBuilder,
                        parcel.get_node_id(),
                        SerializerUtils::marshal(parcel.get_node_state()));
            });
}

IParcel::SerializedParcel FlatBuffersCommanderRequestSerializer::serialize(const CommanderGetServerStatusRequest& parcel)
{
    return build_commander_request_parcel<DcdrFlatBuffers::CommanderGetServerStatusRequest>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetServerStatusRequest(flatBuffersBuilder);
            });
}