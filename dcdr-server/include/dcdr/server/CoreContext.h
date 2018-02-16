#pragma once

#include <dcdr/server/Node.h>
#include <dcdr/server/Connection.h>
#include <dcdr/server/Work.h>
#include <dcdr/server/Scene.h>
#include <dcdr/server/Job.h>

#include <map>

namespace Dcdr::Server
{
    class ServerCoreContext
    {
    public:

    private:
        std::map<size_t, Connection> connections_;

        std::map<uint32_t, Node> nodes_;
        std::map<uint32_t, Work> work_;
        std::map<uint32_t, Scene> scenes_;
        std::map<uint32_t, Job> jobs_;
    };
}