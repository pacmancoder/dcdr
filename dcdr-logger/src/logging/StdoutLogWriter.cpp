#include <dcdr/logging/StdoutLogWriter.h>

#include <iostream>

using namespace Dcdr::Logging;

void StdoutLogWriter::write(ILogWriter::MessageType messageType, const std::string &message)
{
    std::string formatCode = "0";
    switch (messageType)
    {
        case ILogWriter::MessageType::Error:
        {
            formatCode = "1;31";
            break;
        }
        case ILogWriter::MessageType::Warning:
        {
            formatCode = "33";
            break;
        }
        case ILogWriter::MessageType::Info:
        {
            formatCode = "1";
            break;
        }
        case ILogWriter::MessageType::Debug:
        {
            formatCode = "37";
            break;
        }
    }

    std::cout << "\x1b[" << formatCode << "m" << message << "\x1b[0m" << std::endl;
}
