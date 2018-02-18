#pragma once

#include <memory>

namespace Dcdr::Server
{
    class Node;

    class Connection
    {
    public:
        Connection();
        Connection(Connection&& rhs) = default;

        void attach_node(uint32_t node);

        bool is_node_attached() const;
        uint32_t get_node() const;

    private:
        uint32_t node_;
        bool isNodeAttached_;
    };
}