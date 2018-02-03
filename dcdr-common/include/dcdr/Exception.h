#pragma once

#include <exception>
#include <string>

namespace Dcdr
{
    class DcdrException : public std::exception
    {
    public:
        DcdrException(const std::string& subsystem, const std::string& kind, const std::string& message) :
                subsystem_(subsystem),
                kind_(kind),
                message_(message) {}

        std::string to_string()
        {
            return std::string()
                    .append("[")
                    .append(subsystem_)
                    .append("][")
                    .append(kind_)
                    .append("] ")
                    .append(message_);
        }

    private:
        std::string subsystem_;
        std::string kind_;
        std::string message_;
    };
}