#pragma once

#include <dcdr/Exception.h>

namespace Dcdr::Gui
{
    class CommanderException : public DcdrException
    {
    public:
        CommanderException(const std::string& cause, const std::string& message) :
                DcdrException("Commander", cause, message) {}
    };

    class EmptyResponseException : public CommanderException
    {
    public:
        EmptyResponseException(const std::string& message) :
                CommanderException("Communications", message) {}
    };
}