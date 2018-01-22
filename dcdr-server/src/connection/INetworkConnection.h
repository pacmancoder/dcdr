#pragma once

#include <vector>
#include <cstdint>

namespace Dcdr::Server::Connection
{


    class INetworkConnection
    {
    public:
        class IConnectionDataReceiver
        {
        public:
            virtual void receive(const std::vector<uint8_t>& data) = 0;
        };

    public:
        virtual bool is_alive() = 0;
        virtual void send(const std::vector<uint8_t>& data) = 0;
        virtual void set_receiver() = 0;

        virtual ~IConnection() {}
    };
}