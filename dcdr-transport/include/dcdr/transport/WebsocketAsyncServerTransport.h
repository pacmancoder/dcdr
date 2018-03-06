#pragma once

#include <dcdr/transport/IAsyncServerTransport.h>
#include <string>
#include <chrono>

namespace Dcdr::Transport
{
    class WebsocketAsyncServerTransport : public IAsyncServerTransport
    {
    public:
        WebsocketAsyncServerTransport(const std::string& address, std::chrono::milliseconds networkTimeout);

        void register_request_processor(std::shared_ptr<IAsyncConnectionProcessor> requestProcessor) override;
        void run() override;
        void close() override;

        virtual ~WebsocketAsyncServerTransport();
    public:
        struct Impl;

    private:
        std::unique_ptr<Impl> impl_;
    };
}