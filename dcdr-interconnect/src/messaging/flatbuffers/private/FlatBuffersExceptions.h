#pragma once

#include <dcdr/messaging/InterconnectExceptions.h>

namespace Dcdr::Interconnect::FlatBuffers
{
    class FlatBuffersVerificationException : public DeserializationException
    {
    public:
        FlatBuffersVerificationException() :
                DeserializationException("FlatBuffer verification has been failed") {}
    };
}