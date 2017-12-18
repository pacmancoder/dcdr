#include <dcdr/messaging/ClientConnection.h>

Dcdr::Interconnect::ClientConnection::ClientConnection(const std::array<uint8_t, 16> &connectionId) :
    connectionId_(connectionId) {}

const std::array<uint8_t, 16> &Dcdr::Interconnect::ClientConnection::get_id() const
{
    return connectionId_;
}
