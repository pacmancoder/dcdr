#include <dcdr/server/Connection.h>

using namespace Dcdr::Server;

Connection::Connection() :
    node_(nullptr) {}

void Connection::attach_node(std::shared_ptr<Node> node)
{
    node_ = std::move(node);
}

bool Connection::node_is_attached()
{
    return node_ == nullptr;
}

Node& Connection::get_node()
{
    return *node_.get();
}
