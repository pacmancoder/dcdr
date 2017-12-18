#include <dcdr/messaging/ServerConnection.h>

using namespace Dcdr::Interconnect;

ServerConnection::ServerConnection(ClientConnectionPtr clientConnection) :
    clientConnection_(std::move(clientConnection)) {}

const ClientConnection &ServerConnection::get_client_connection() {
    return *clientConnection_;
}
