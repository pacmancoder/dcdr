#pragma once

#include <dcdr/transport/ISyncClientTransport.h>
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <chrono>

namespace Dcdr::Transport
{
    class WebsocketSyncClientTransport : public ISyncClientTransport
    {
    public:
        WebsocketSyncClientTransport(const std::string& address, std::chrono::milliseconds networkTimeout);

        void send_request(const Request& request) override;
        ResponsePtr get_response(const Request& request) override;

        virtual ~WebsocketSyncClientTransport();

    private:
        void send(const Request& data);
        ResponsePtr receive();

    public:
        struct Impl;

    private:
        std::unique_ptr<Impl> impl_;
    };
}