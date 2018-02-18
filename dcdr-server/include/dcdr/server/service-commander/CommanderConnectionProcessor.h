#pragma once

#include <dcdr/transport/IAsyncConnectionProcessor.h>

#include <dcdr/messaging/IParcelDispatcher.h>
#include <dcdr/messaging/commander/ICommanderRequestDispatcher.h>

#include <memory>

namespace Dcdr::Server
{
    class CoreContext;

    class CommanderConnectionProcessor :
            public Transport::IAsyncConnectionProcessor,
            public Interconnect::IParcelDispatcher,
            public Interconnect::ICommanderRequestDispatcher
    {
    public:
        explicit CommanderConnectionProcessor(std::shared_ptr<CoreContext>& coreContext);

        // IAsyncConnectionProcessor
        uint32_t open_connection() override;
        ResponseHandle get_response(uint32_t id, const Request& request) override;
        void close_connection(uint32_t id) override;

        // IParcel dispatcher
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::ACommanderRequestParcel& parcel) override;

        // ICommanderRequestDespatcher
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderGetJobListRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderGetJobInfoRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderGetJobPreviewRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderGetJobArtifactRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderSetJobStateRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderAddJobRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderGetSceneListRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderGetNodeListRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderGetNodeInfoRequest& request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::CommanderSetNodeStateRequest& request) override;

    private:
        std::shared_ptr<CoreContext> coreContext_;
    };
}