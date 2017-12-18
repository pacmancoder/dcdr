#pragma once

#include <vector>
#include <cstdint>
#include <memory>
#include <string>

namespace Dcdr::Interconnect
{
    class IRequest;

    class IRequestDeserializer
    {
    public:
        typedef std::unique_ptr<IRequest> IRequestPtr;

    public:
        virtual void deserialize(const std::vector<uint8_t >& buffer) = 0;

        virtual std::string get_connection() = 0;
        virtual IRequestPtr get_request() = 0;

        ~IRequestDeserializer() = default;
    };
}