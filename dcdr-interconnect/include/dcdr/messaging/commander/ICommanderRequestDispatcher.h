#pragma once

#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{
    // jobs
    class CommanderGetJobListRequest;
    class CommanderGetJobInfoRequest;
    class CommanderGetJobPreviewRequest;
    class CommanderGetJobArtifactRequest;
    class CommanderSetJobStateRequest;
    class CommanderAddJobRequest;
    // scenes
    class CommanderGetSceneListRequest;
    // nodes
    class CommanderGetNodeListRequest;
    class CommanderGetNodeInfoRequest;
    class CommanderSetNodeStateRequest;

    class ICommanderRequestDispatcher
    {
    public:
        // jobs
        virtual IParcel::ParcelHandle dispatch(const CommanderGetJobListRequest& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderGetJobInfoRequest& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderGetJobPreviewRequest& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderGetJobArtifactRequest& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderSetJobStateRequest& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderAddJobRequest& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderGetSceneListRequest& parcel) = 0;
        // nodes
        virtual IParcel::ParcelHandle dispatch(const CommanderGetNodeListRequest& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderGetNodeInfoRequest& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const CommanderSetNodeStateRequest& parcel) = 0;

        virtual ~ICommanderRequestDispatcher() = default;

    };
}