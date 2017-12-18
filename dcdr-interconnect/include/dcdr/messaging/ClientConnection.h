#pragma once

#include <string>
#include <array>

namespace Dcdr::Interconnect
{
    class ClientConnection
    {
    public:
        explicit ClientConnection(const std::array<uint8_t, 16>& connectionId);

        const std::array<uint8_t, 16>& get_id() const;

    private:
        std::array<uint8_t, 16> connectionId_;
    };
}