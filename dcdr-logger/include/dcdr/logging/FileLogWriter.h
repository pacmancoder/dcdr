#pragma once

#include <dcdr/logging/ILogWriter.h>
#include <fstream>

namespace Dcdr::Logging
{
    class FileLogWriter : public ILogWriter
    {
    public:
        explicit FileLogWriter(const std::string& file_path);

        void write(MessageType messageType, const std::string& message) override;

    private:
        std::ofstream file_;
    };
}
