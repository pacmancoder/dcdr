#pragma once

#include <string>

namespace Dcdr::Logging
{
    class ILogWriter
    {
    public:
        enum class MessageType
        {
            Error,
            Warning,
            Info,
            Debug
        };

        virtual void write(MessageType messageType, const std::string& message) = 0;

        virtual ~ILogWriter() {}
    };
}