#pragma once

namespace Dcdr::Interconnect
{
    class ConnectRequest;

    class IRequestProcessor
    {
    public:
        virtual void process_request(const ConnectRequest& request) = 0;

        virtual ~IRequestProcessor() = default;
    };
}