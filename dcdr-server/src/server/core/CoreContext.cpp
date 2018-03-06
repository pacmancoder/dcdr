#include <dcdr/server/core/CoreContext.h>

#include <functional>

using namespace Dcdr::Server;
using namespace std::placeholders;

CoreContext::CoreContext() :
    scenes_(),
    nodes_(),
    connections_(nullptr, std::bind(&CoreContext::on_delete_connection, this, _1)),
    jobs_(),
    tasks_()
{

}

void CoreContext::on_delete_connection(uint32_t connectionId)
{
    connections_.access_read(connectionId,
        [this](const Connection& connection)
        {
           if (connection.is_node_attached())
           {
               if (nodes_.exists(connection.get_node()))
               {
                   nodes_.remove(connection.get_node());
               }
           }
        });
}

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
