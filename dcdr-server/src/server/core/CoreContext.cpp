#include <dcdr/server/core/CoreContext.h>

using namespace Dcdr::Server;

SharedResourceManager<Scene>& CoreContext::get_scenes()
{
    return scenes_;
}

SharedResourceManager<Node>& CoreContext::get_nodes()
{
    return nodes_;
}

SharedResourceManager<Connection>& CoreContext::get_connections()
{
    return connections_;
}

SharedResourceManager<Job>& CoreContext::get_jobs()
{
    return jobs_;
}

SharedResourceManager<ChunkTask>& CoreContext::get_tasks()
{
    return tasks_;
}
