#pragma once

#include <dcdr/messaging/IParcelDispatcher.h>
#include <dcdr/messaging/worker/IWorkerRequestDispatcher.h>
#include <dcdr/server/core/CoreContext.h>

#include <optional>

namespace Dcdr::Server
{
    class WorkerRouter :
            public Interconnect::IParcelDispatcher,
            public Interconnect::IWorkerRequestDispatcher
    {
    public:
        explicit WorkerRouter(const std::shared_ptr<CoreContext>& coreContext);
        ~WorkerRouter() override;

        uint32_t get_connection_id();

        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::AWorkerRequestParcel &parcel) override;

        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::WorkerLoginRequest &request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::WorkerLogoutRequest &request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::WorkerSendHardwareInfoRequest &request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::WorkerPollTasksRequest &request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::WorkerCommitTasksRequest &request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::WorkerDownloadSceneRequest &request) override;
        Interconnect::IParcel::ParcelPtr dispatch(const Interconnect::WorkerGetSceneInfoRequest &request) override;

    private:
        uint32_t connectionId_;
        std::shared_ptr<CoreContext> coreContext_;
    };
}
