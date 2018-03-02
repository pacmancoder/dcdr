#pragma once

#include <dcdr/transport/IAsyncConnectionProcessor.h>
#include <dcdr/server/service-commander/CommanderRouter.h>

#include <memory>

namespace Dcdr::Server
{
    class CoreContext;

    class CommanderService : public Transport::IAsyncConnectionProcessor
    {
    public:
        explicit CommanderService(std::shared_ptr<CoreContext>& coreContext);

        uint32_t open_connection() override;
        ResponseHandle get_response(uint32_t id, const Request& request) override;
        void close_connection(uint32_t id) override;

    private:
        std::shared_ptr<CoreContext> coreContext_;
        std::unique_ptr<CommanderRouter> commanderRouter_;
    };
}