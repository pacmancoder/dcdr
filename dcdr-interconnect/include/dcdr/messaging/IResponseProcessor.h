#pragma once

namespace Dcdr::Interconnect
{
    class ConnectRequest;

    class IResponseProcessor
    {
    public:
        virtual void process(const ConnectRequest& request) = 0;

        virtual ~IResponseProcessor() = default;
    };
}