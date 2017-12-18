#pragma once

#include <string>

namespace Dcdr::Interconnect
{
    class ServerConnection

    class IServerConnectionResolver
    {
    public:

        virtual ServerConnection& get_connection(const std::string connection_id) = 0;

        virtual ~IServerConnectionResolver() = default;
    };

}