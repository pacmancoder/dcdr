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
    class CommanderGetSceneListRequest;
    // nodes
    class CommanderGetNodeListRequest;
    class CommanderGetNodeInfoRequest;
    class CommanderSetNodeStateRequest;

    class ACommanderRequestParcelDispatcher
    {
    public:
        // jobs
        virtual IParcel::ParcelHandle dispatch(const CommanderGetJobListRequest& parcel);
        virtual IParcel::ParcelHandle dispatch(const CommanderGetJobInfoRequest& parcel);
        virtual IParcel::ParcelHandle dispatch(const CommanderGetJobPreviewRequest& parcel);
        virtual IParcel::ParcelHandle dispatch(const CommanderGetJobArtifactRequest& parcel);
        virtual IParcel::ParcelHandle dispatch(const CommanderSetJobStateRequest& parcel);
        virtual IParcel::ParcelHandle dispatch(const CommanderAddJobRequest& parcel);
        virtual IParcel::ParcelHandle dispatch(const CommanderGetSceneListRequest& parcel);
        // nodes
        virtual IParcel::ParcelHandle dispatch(const CommanderGetNodeListRequest& parcel);
        virtual IParcel::ParcelHandle dispatch(const CommanderGetNodeInfoRequest& parcel);
        virtual IParcel::ParcelHandle dispatch(const CommanderSetNodeStateRequest& parcel);

        virtual ~ACommanderRequestParcelDispatcher() = default;

    protected:
        virtual IParcel::ParcelHandle dispatch_not_supported();

    private:

    };
}