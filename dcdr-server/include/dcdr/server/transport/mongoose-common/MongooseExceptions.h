#pragma once

#include <dcdr/server/transport/TransportExceptions.h>

namespace Dcdr::Server
{
    class MongooseException : WebServerException
    {
    public:
        explicit MongooseException(const std::string& msg) :
                WebServerException("Mongoose", msg) {}
    };
}