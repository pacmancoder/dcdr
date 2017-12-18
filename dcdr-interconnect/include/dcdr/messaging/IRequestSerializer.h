#pragma once

#include <vector>
#include <cstdint>
#include <memory>

namespace Dcdr::Interconnect
{
    class IRequest;
    class ConnectRequest;

    class IRequestSerializer
    {
    public:
        typedef std::unique_ptr<IRequest> IRequestPtr;

    public:
        virtual void set_request(IRequestPtr request) = 0;
        virtual void set_connection(const std::string& connection) = 0;

        virtual std::vector<uint8_t> serialize() = 0;

        virtual ~IRequestSerializer() = default;

    protected:
        friend class ConnectRequest;
        virtual std::vector<uint8_t> serialize(const ConnectRequest& request) = 0;
    };
}
