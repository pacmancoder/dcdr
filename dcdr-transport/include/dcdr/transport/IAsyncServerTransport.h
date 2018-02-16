#pragma once

#include <vector>
#include <cstdint>
#include <memory>

#include <dcdr/transport/IAsyncRequestProcessor.h>

namespace Dcdr::Transport
{
    class IAsyncServerTransport
    {
    public:
        virtual void register_request_processor(std::shared_ptr<IAsyncRequestProcessor> requestProcessor) = 0;

        virtual void run() = 0;
        virtual void close() = 0;

        virtual ~IAsyncServerTransport() {}
    };
}