#pragma once

namespace Dcdr::Interconnect
{
    // job
    class CommanderGetJobListResponse;
    class CommanderGetJobInfoResponse;
    class CommanderGetJobPreviewResponse;
    class CommanderGetJobArtifactResponse;
    class CommanderDoJobListUpdateResponse;
    // scene
    class CommanderGetSceneListResponse;
    // node
    class CommanderGetNodeListResponse;
    class CommanderGetNodeInfoResponse;
    class CommanderDoNodeListUpdateResponse;
    // common
    class CommanderDoShowErrorResponse;

    class ICommanderResponseSerializer
    {
    public:

        virtual IParcel::SerializedParcel serialize(const CommanderGetJobListResponse& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderGetJobInfoResponse& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderGetJobPreviewResponse& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderGetJobArtifactResponse& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderDoJobListUpdateResponse& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderGetSceneListResponse& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderGetNodeListResponse& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderGetNodeInfoResponse& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderDoNodeListUpdateResponse& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderDoShowErrorResponse& parcel) = 0;

        virtual ~ICommanderResponseSerializer() = default;
    };
}