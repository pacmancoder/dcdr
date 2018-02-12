#pragma once

namespace Dcdr::Interconnect
{
    // commander job requests
    class CommanderGetJobListRequest;
    class CommanderGetJobInfoRequest;
    class CommanderGetJobPreviewRequest;
    class CommanderGetJobArtifactRequest;
    class CommanderSetJobStateRequest;
    class CommanderAddJobRequest;
    // scenes
    class CommanderGetSceneListRequest;
    // commander node requests
    class CommanderGetNodeListRequest;
    class CommanderGetNodeInfoRequest;
    class CommanderSetNodeStateRequest;

    class ICommanderRequestSerializer
    {
    public:

        virtual IParcel::SerializedParcel serialize(const CommanderGetJobListRequest& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderGetJobInfoRequest& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderGetJobPreviewRequest& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderGetJobArtifactRequest& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderSetJobStateRequest& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderAddJobRequest& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderGetSceneListRequest& parcel) = 0;

        virtual IParcel::SerializedParcel serialize(const CommanderGetNodeListRequest& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderGetNodeInfoRequest& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderSetNodeStateRequest& parcel) = 0;

        virtual ~ICommanderRequestSerializer() = default;
    };
}