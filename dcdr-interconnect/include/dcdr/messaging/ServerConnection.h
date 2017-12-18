#pragma once

#include <dcdr/messaging/ClientConnection.h>
#include <memory>

namespace Dcdr::Interconnect
{
    class ServerConnection
    {
    public:
        typedef std::unique_ptr<ClientConnection> ClientConnectionPtr;

    public:
        explicit ServerConnection(ClientConnectionPtr clientConnection);

        const ClientConnection& get_client_connection();

    private:
        ClientConnectionPtr clientConnection_;
    };
}