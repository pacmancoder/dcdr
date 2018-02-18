#pragma once

#include <dcdr/Exception.h>

namespace Dcdr::Server
{
    class ServerException : public DcdrException
    {
    public:
        ServerException(const std::string& kind, const std::string& message) :
                DcdrException("Server", kind, message) {}
    };

    class SceneException : public ServerException
    {
    public:
        explicit SceneException(const std::string& message) :
                ServerException("Scene", message) {}
    };

    class ChunkException : public ServerException
    {
    public:
        explicit ChunkException(const std::string& message) :
                ServerException("Chunk", message) {}
    };

    class ConnectionException : public ServerException
    {
    public:
        explicit  ConnectionException(const std::string& message) :
                ServerException("Connection", message) {}
    };
}