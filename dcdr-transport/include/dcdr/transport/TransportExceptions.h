#pragma once

#include <dcdr/Exception.h>

namespace Dcdr::Transport
{
    class TransportException : public DcdrException
    {
    public:
        TransportException(const std::string& kind, const std::string& message) :
                DcdrException("Transport", kind, message) {}
    };

    class ConnectionException : public TransportException
    {
    public:
        explicit ConnectionException(const std::string& message) :
                TransportException("Connection", message) {}
    };

}