#pragma once

#include <dcdr/messaging/IParcelDispatcher.h>
#include <dcdr/messaging/commander/ICommanderRequestDispatcher.h>

#include <dcdr/server/core/CoreContext.h>

#include <memory>

namespace Dcdr::Server
{
    class CommanderRouter :
            public Interconnect::IParcelDispatcher,
            public Interconnect::ICommanderRequestDispatcher
    {
    public:

        explicit CommanderRouter(const std::shared_ptr<CoreContext>& coreContext);

        // IParcel dispatcher
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::ACommanderRequestParcel& parcel) override;

        // ICommanderRequestDespatcher
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderGetJobListRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderGetJobInfoRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderGetJobArtifactRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderSetJobStateRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderAddJobRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderGetSceneListRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderGetNodeListRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderGetNodeInfoRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderSetNodeStateRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderGetServerStatusRequest& request) override;

    private:
        std::shared_ptr<CoreContext> coreContext_;
    };
}