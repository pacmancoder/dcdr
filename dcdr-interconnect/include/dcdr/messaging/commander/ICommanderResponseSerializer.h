#pragma once

namespace Dcdr::Interconnect
{
    // job
    class CommanderGetJobListResponse;
    class CommanderGetJobInfoResponse;
    class CommanderGetJobArtifactResponse;
    // scene
    class CommanderGetSceneListResponse;
    // node
    class CommanderGetNodeListResponse;
    class CommanderGetNodeInfoResponse;
    // common
    class CommanderErrorResponse;
    // status
    class CommanderGetServerStatusResponse;

    class ICommanderResponseSerializer
    {
    public:

        virtual IParcel::SerializedParcel serialize(const CommanderGetJobListResponse& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderGetJobInfoResponse& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderGetJobArtifactResponse& parcel) = 0;

        virtual IParcel::SerializedParcel serialize(const CommanderGetSceneListResponse& parcel) = 0;

        virtual IParcel::SerializedParcel serialize(const CommanderGetNodeListResponse& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const CommanderGetNodeInfoResponse& parcel) = 0;

        virtual IParcel::SerializedParcel serialize(const CommanderErrorResponse& parcel) = 0;

        virtual IParcel::SerializedParcel serialize(const CommanderGetServerStatusResponse& parcel) = 0;

        virtual ~ICommanderResponseSerializer() = default;
    };
}