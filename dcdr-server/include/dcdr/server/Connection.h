#pragma once

#include <memory>

namespace Dcdr::Server
{
    class Node;

    class Connection
    {
    public:
        Connection();

        void attach_node(std::shared_ptr<Node> node);

        bool node_is_attached();
        Node& get_node();

    private:
        std::shared_ptr<Node> node_;
    };
}