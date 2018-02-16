#pragma once

#include <vector>
#include <cstdint>
#include <memory>

#include <dcdr/transport/IAsyncConnectionProcessor.h>

namespace Dcdr::Transport
{
    class IAsyncServerTransport
    {
    public:
        virtual void register_request_processor(std::shared_ptr<IAsyncConnectionProcessor> requestProcessor) = 0;

        virtual void run() = 0;
        virtual void close() = 0;

        virtual ~IAsyncServerTransport() {}
    };
}