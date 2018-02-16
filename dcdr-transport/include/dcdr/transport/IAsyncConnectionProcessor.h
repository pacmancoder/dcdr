#pragma once

#include <memory>
#include <future>
#include <vector>

namespace Dcdr::Transport
{
    class IAsyncConnectionProcessor
    {
    public:
        using Request = std::vector<uint8_t>;
        using ResponseHandle = std::future<std::vector<uint8_t>>;

    public:
        virtual void open_connection(size_t id) = 0;
        virtual ResponseHandle get_response(size_t id, const Request& request) = 0;
        virtual void close_connection(size_t id) = 0;

        virtual ~IAsyncConnectionProcessor() = default;
    };
}