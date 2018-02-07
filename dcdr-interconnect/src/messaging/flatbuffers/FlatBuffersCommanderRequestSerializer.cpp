#include <dcdr/messaging/flatbuffers/FlatBuffersCommanderRequestSerializer.h>
#include <dcdr/logging/Logger.h>
#include <dcdr/messaging/commander/CommanderRequests.h>
#include <flatbuffers-generated/DcdrFlatBuffers.h>
#include <iostream>
#include <stdexcept>

using namespace Dcdr::Logging;
using namespace Dcdr::Interconnect;

// internal helpers for building FlatBuffers
#include <messaging/flatbuffers/FlatBuffersBuilders.h>

namespace
{
    const size_t COMMANDER_REQUEST_BUILDER_BUFFER_SIZE = 128;

    template <class RequestType, class ParcelGenerator>
    IParcel::SerializedParcel build_commander_request_parcel(ParcelGenerator&& parcelGenerator)
    {
        return build_parcel<DcdrFlatBuffers::CommanderRequest>(
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

    DcdrFlatBuffers::JobState marshal(JobState jobState)
    {
        switch (jobState)
        {
            case JobState::InProgress: return DcdrFlatBuffers::JobState_InProgress;
            case JobState::Stopped:    return DcdrFlatBuffers::JobState_Stopped;
            case JobState::Removed:    return DcdrFlatBuffers::JobState_Removed;
        }
        throw std::invalid_argument("Unreachable code!"); // make linter happy
    }

    DcdrFlatBuffers::NodeState marshal(NodeState nodeState)
    {
        switch (nodeState)
        {
            case NodeState::Active:        return DcdrFlatBuffers::NodeState_Active;
            case NodeState::Disabled:      return DcdrFlatBuffers::NodeState_Disabled;
            case NodeState::Malfunctioned: return DcdrFlatBuffers::NodeState_Malfunctioned;
            case NodeState::Offline:       return DcdrFlatBuffers::NodeState_Offline;
        }
        throw std::invalid_argument("Unreachable code!"); // make linter happy
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

IParcel::SerializedParcel FlatBuffersCommanderRequestSerializer::serialize(const CommanderGetJobPreviewRequest& parcel)
{
    return build_commander_request_parcel<DcdrFlatBuffers::CommanderGetJobPreviewRequest>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetJobPreviewRequest(
                        flatBuffersBuilder,
                        parcel.get_job_id(),
                        parcel.get_mipmap_level());
            });
}

IParcel::SerializedParcel FlatBuffersCommanderRequestSerializer::serialize(const CommanderGetJobArtifactRequest& parcel)
{
    return build_commander_request_parcel<DcdrFlatBuffers::CommanderGetJobArtifactRequest>(
            [&parcel](auto& flatBuffersBuilder)
            {
                return DcdrFlatBuffers::CreateCommanderGetJobArtifactRequest(
                        flatBuffersBuilder,
                        parcel.get_job_id());
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
                        marshal(parcel.get_job_state()));
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
                        marshal(parcel.get_node_state()));
            });
}