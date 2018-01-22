#pragma once

#include <dcdr/Exception.h>

namespace Dcdr::Interconnect
{
    class InterconnectException : public DcdrException
    {
    public:
        InterconnectException(const std::string& kind, const std::string& msg) :
                DcdrException("Interconnect", kind, msg) {}
    };

    class DeserializationException : public InterconnectException
    {
    public:
        DeserializationException(const std::string& msg) :
                InterconnectException("Deserialization", msg) {}
    };
}