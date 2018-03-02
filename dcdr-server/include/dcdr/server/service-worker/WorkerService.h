#pragma once

#include <dcdr/transport/IAsyncConnectionProcessor.h>
#include <dcdr/server/core/CoreContext.h>
#include <dcdr/server/service-worker/WorkerRouter.h>

#include <memory>
#include <map>

namespace Dcdr::Server
{
    class WorkerService : public Transport::IAsyncConnectionProcessor
    {
    public:
        explicit WorkerService(const std::shared_ptr<CoreContext>& coreContext);

        uint32_t open_connection() override;
        ResponseHandle get_response(uint32_t id, const Request &request) override;
        void close_connection(uint32_t id) override;

    private:
        std::shared_ptr<CoreContext> coreContext_;
        std::map<uint32_t, std::unique_ptr<WorkerRouter>> routers_;
    };
}