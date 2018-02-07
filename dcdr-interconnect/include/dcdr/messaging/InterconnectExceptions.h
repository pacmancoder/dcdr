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
        explicit DeserializationException(const std::string& msg) :
                InterconnectException("Deserialization", msg) {}
    };

    class DeserializationNotImplementedException : public DeserializationException
    {
    public:
        explicit DeserializationNotImplementedException(const std::string& parcelName) :
                DeserializationException(
                        std::string("Deserialization for ") + parcelName + std::string(" parcel is not implemented")) {}
    };

    class SerializationException : public InterconnectException
    {
    public:
        explicit SerializationException(const std::string& msg) :
                InterconnectException("Serialization", msg) {}
    };

    class SerializationNotImplementedException : public SerializationException
    {
    public:
        explicit SerializationNotImplementedException(const std::string& parcelName) :
                SerializationException(
                        std::string("Serialization for ") + parcelName + std::string(" parcel is not implemented")) {}
    };
}