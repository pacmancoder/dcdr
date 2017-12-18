#pragma once

#include <dcdr/messaging/IRequestSerializer.h>
#include <dcdr/messaging/IRequestProcessor.h>

#include <memory>
#include <cstdint>

namespace Dcdr::Interconnect
{
    class IRequest
    {
    public:
        virtual std::vector<uint8_t> serialize(IRequestSerializer& serializer) const = 0;
        virtual void process_request(IRequestProcessor& requestProcessor) const = 0;

        virtual ~IRequest() = default;
    };
}