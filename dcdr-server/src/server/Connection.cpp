#include <dcdr/server/Connection.h>

#include <dcdr/server/ServerExceptions.h>

using namespace Dcdr::Server;

Connection::Connection() :
    node_(0),
    isNodeAttached_(false) {}


void Connection::attach_node(uint32_t node)
{
    node_ = node;
    isNodeAttached_ = true;
}

bool Connection::is_node_attached() const
{
    return  isNodeAttached_;
}

uint32_t Connection::get_node() const
{
    if (!isNodeAttached_)
    {
        throw ConnectionException("Node is not attached to the connection");
    }
    return node_;
}
