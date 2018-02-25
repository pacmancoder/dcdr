#pragma once

#include <vector>
#include <cstdint>
#include <memory>

namespace Dcdr::Transport
{
    class ISyncClientTransport
    {
    public:
        using Request = std::vector<uint8_t>;
        using Response = std::vector<uint8_t>;
        using ResponsePtr = std::unique_ptr<std::vector<uint8_t>>;

    public:
        virtual void send_request(const Request& request) = 0;
        virtual ResponsePtr get_response(const Request& request) = 0;

        virtual ~ISyncClientTransport() = default;
    };

}