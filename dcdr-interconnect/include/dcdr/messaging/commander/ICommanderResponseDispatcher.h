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

    class ICommanderResponseDispatcher
    {
    public:

        virtual IParcel::ParcelHandle dispatch(const CommanderGetJobListResponse& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderGetJobInfoResponse& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderGetJobPreviewResponse& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderGetJobArtifactResponse& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderDoJobListUpdateResponse& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderGetSceneListResponse& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderGetNodeListResponse& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderGetNodeInfoResponse& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderDoNodeListUpdateResponse& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderDoShowErrorResponse& parcel) = 0;

        virtual ~ICommanderResponseDispatcher() = default;
    };
}