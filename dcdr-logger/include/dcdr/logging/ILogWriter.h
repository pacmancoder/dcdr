#pragma once

#include <string>

namespace Dcdr::Logging
{
    enum class LogCategory
    {
        Error,
        Warning,
        Info,
        Debug,
        Trace
    };


    class ILogWriter
    {
    public:
        virtual void write(LogCategory messageType, const std::string& message) = 0;

        virtual ~ILogWriter() = default;
    };
}