#include <dcdr/logging/FileLogWriter.h>

Dcdr::Logging::FileLogWriter::FileLogWriter(const std::string &file_path) :
    file_(file_path) {}

void Dcdr::Logging::FileLogWriter::write(Dcdr::Logging::ILogWriter::MessageType, const std::string &message)
{
    file_ << message;
}
