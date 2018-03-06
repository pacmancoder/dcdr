#include <dcdr/logging/FileLogWriter.h>

using namespace Dcdr::Logging;

FileLogWriter::FileLogWriter(const std::string &file_path) :
    file_(file_path) {}

void FileLogWriter::write(LogCategory, const std::string &message)
{
    file_ << message;
}
