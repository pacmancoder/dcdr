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
        using Response = std::vector<uint8_t>;
        using ResponseHandle = std::future<Response>;

    public:
        // should return new connection id
        virtual uint32_t open_connection() = 0;
        virtual ResponseHandle get_response(uint32_t id, const Request& request) = 0;
        virtual void close_connection(uint32_t id) = 0;

        virtual ~IAsyncConnectionProcessor() = default;
    };
}