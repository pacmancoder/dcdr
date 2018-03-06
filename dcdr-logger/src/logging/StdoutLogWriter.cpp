#include <dcdr/logging/StdoutLogWriter.h>

#include <iostream>

using namespace Dcdr::Logging;

void StdoutLogWriter::write(LogCategory category, const std::string &message)
{
    std::string formatCode = "0";
    switch (category)
    {
        case LogCategory::Error:
        {
            formatCode = "1;31";
            break;
        }
        case LogCategory::Warning:
        {
            formatCode = "33";
            break;
        }
        case LogCategory::Info:
        {
            formatCode = "1";
            break;
        }
        case LogCategory::Debug:
        {
            formatCode = "37";
            break;
        }
        case LogCategory::Trace:
        {
            formatCode = "94";
            break;
        }
    }

    std::cout << "\x1b[" << formatCode << "m" << message << "\x1b[0m" << std::endl;
}
