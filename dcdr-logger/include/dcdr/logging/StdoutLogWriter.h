#pragma once

#include <dcdr/logging/ILogWriter.h>

namespace Dcdr::Logging
{
    class StdoutLogWriter : public ILogWriter
    {
    public:
        void write(LogCategory messageType, const std::string& message) override;

    };
}