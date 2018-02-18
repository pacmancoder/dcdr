#pragma once

#include <dcdr/server/core/Node.h>
#include <dcdr/server/core/Connection.h>
#include <dcdr/server/core/Work.h>
#include <dcdr/server/core/Scene.h>
#include <dcdr/server/core/Job.h>

#include <dcdr/server/core/SharedResourceManager.h>

namespace Dcdr::Server
{
    /// @brief provides facade for server core entities
    /// @remark class is thread-safe
    class CoreContext
    {
    public:
        SharedResourceManager<Scene>& get_scenes();
        SharedResourceManager<Node>& get_nodes();
        SharedResourceManager<Connection>& get_connections();
        SharedResourceManager<Job>& get_jobs();
        SharedResourceManager<Work>& get_works();

    private:
        SharedResourceManager<Scene> scenes_;
        SharedResourceManager<Node> nodes_;
        SharedResourceManager<Connection> connections_;
        SharedResourceManager<Job> jobs_;
        SharedResourceManager<Work> works_;

    };
}