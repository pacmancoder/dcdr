#pragma once

#include <dcdr/Exception.h>

namespace Dcdr::Server
{
    class WebServerException : DcdrException
    {
    public:
        WebServerException(const std::string& kind, const std::string& msg) :
                DcdrException("Web server", kind, msg) {}
    };

    class MongooseException : WebServerException
    {
    public:
        explicit MongooseException(const std::string& msg) :
                WebServerException("Mongoose", msg) {}
    };
}