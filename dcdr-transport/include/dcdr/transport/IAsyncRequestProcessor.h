#pragma once

#include <memory>
#include <future>
#include <vector>

namespace Dcdr::Transport
{
    class IAsyncRequestProcessor
    {
    public:
        using Request = std::vector<uint8_t>;
        using ResponseHandle = std::future<std::vector<uint8_t>>;

    public:
        virtual ResponseHandle process_request(const Request& request) = 0;

        virtual ~IAsyncRequestProcessor() = default;
    };
}