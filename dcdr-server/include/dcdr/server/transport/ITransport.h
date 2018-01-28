#pragma once

namespace Dcdr::Server
{
    class ITransport
    {
    public:
        virtual void open() = 0;

        virtual void close() = 0;

        virtual ~ITransport() = default;
    };
}