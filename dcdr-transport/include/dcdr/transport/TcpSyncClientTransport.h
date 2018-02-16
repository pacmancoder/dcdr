#pragma once

#include <dcdr/transport/ISyncClientTransport.h>
#include <cstdint>
#include <string>
#include <memory>
#include <vector>
#include <chrono>

namespace Dcdr::Transport
{
    class TcpSyncClientTransport : public ISyncClientTransport
    {
    public:
        TcpSyncClientTransport(const std::string& address, std::chrono::milliseconds networkTimeout);

        ResponsePtr get_response(const Request& request) override;

        virtual ~TcpSyncClientTransport();

    private:
        void send(const Request& data);
        ResponsePtr receive();

    public:
        struct Impl;

    private:
        std::unique_ptr<Impl> impl_;
    };
}