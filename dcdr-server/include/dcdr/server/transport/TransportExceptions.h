#pragma once

#include <dcdr/Exception.h>

namespace Dcdr::Server
{
    class WebServerException : public DcdrException
    {
    public:
        WebServerException(const std::string& kind, const std::string& msg) :
                DcdrException("Web server", kind, msg) {}
    };
}