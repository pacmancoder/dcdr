#pragma once

#include <dcdr/messaging/IResponseSerializer.h>
#include <dcdr/messaging/IResponseProcessor.h>

namespace Dcdr::Interconnect
{
    class IResponse
    {
    public:
        virtual void serialize(IResponseSerializer& serializer) = 0;
        virtual void processResponse(IResponseProcessor& requestProcessor) = 0;

        virtual ~IRequest() = default;
    };
}