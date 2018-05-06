#include <dcdr/server/service-commander/CommanderRouter.h>

#include <dcdr/logging/Logger.h>

#include <dcdr/messaging/commander/CommanderRequestParcels.h>
#include <dcdr/messaging/commander/CommanderResponseParcels.h>

#include <string>

using namespace Dcdr::Server;
using namespace Dcdr::Interconnect;
using namespace Dcdr::Logging;

namespace
{
    const char* LOG_PREFIX = "[Server][CommandRouter] ";
    const uint16_t DEFAULT_CHUNK_SIZE = 32;

    std::string generate_scene_name(const Job& job, CoreContext& context)
    {
        std::string sceneName;

        context.get_scenes().access_read(job.get_scene_id(), [&sceneName](const Scene& scene)
        {
            sceneName = scene.get_name();
        });

        sceneName.append(" (")
                 .append(std::to_string(job.get_width()))
                 .append("x")
                 .append(std::to_string(job.get_height()))
                 .append(")");

        return sceneName;
    }
}

CommanderRouter::CommanderRouter(const std::shared_ptr<CoreContext>& coreContext) :
        coreContext_(coreContext) {}

IParcel::ParcelPtr CommanderRouter::dispatch(const ACommanderRequestParcel& parcel)
{
    return parcel.dispatch(static_cast<ICommanderRequestDispatcher&>(*this));
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderGetSceneListRequest&)
{
    std::vector<Commander::Scene> scenes;

    coreContext_->get_scenes().iterate_const([&scenes](uint32_t id, const Scene& scene)
    {
        scenes.emplace_back(Commander::Scene {id, scene.get_name(), scene.get_width(), scene.get_height()});
    });

    return std::make_unique<CommanderGetSceneListReponseParcel>(std::move(scenes));
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderGetJobListRequest&)
{
    std::vector<Commander::Job> jobs;

    coreContext_->get_jobs().iterate_const([this, &jobs](uint32_t id, const Job& job)
    {
        jobs.emplace_back(Commander::Job {
               id,
               generate_scene_name(job, *coreContext_),
               job.get_state()
        });
    });

    return std::make_unique<CommanderGetJobListResponseParcel>(std::move(jobs));
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderGetJobInfoRequest& request)
{
    std::vector<PropertyPair> properties;

    coreContext_->get_jobs().access_read(request.get_job_id(), [&properties](const Job& job)
    {
        for (const auto& property : job.get_all_properties())
        {
            properties.emplace_back(PropertyPair {property.first, property.second});
        }
    });

    return std::make_unique<CommanderGetJobInfoResponseParcel>(request.get_job_id(), std::move(properties));
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderGetJobArtifactRequest& request)
{
    IParcel::ParcelPtr response = nullptr;

    coreContext_->get_jobs().access_read(request.get_job_id(),
    [&request, &response](const Job& job)
    {
        auto surfaceBuffer =
                job.get_readonly_surface().get_surface_buffer(request.get_format(), request.get_mipmap_level());

        response = std::make_unique<CommanderGetJobArtifactResponseParcel>(
                request.get_job_id(),
                surfaceBuffer.format,
                surfaceBuffer.width,
                surfaceBuffer.height,
                std::move(surfaceBuffer.data));
    });

    return response;
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderSetJobStateRequest& request)
{
    if (request.get_job_state() == Interconnect::Commander::JobState::Removed)
    {
        coreContext_->get_jobs().remove(request.get_job_id());
    }
    else
    {
        coreContext_->get_jobs().access_write(
                request.get_job_id(),
                [&request](Job& job)
                {
                    job.set_state(request.get_job_state());
                });
    }
    return std::make_unique<CommanderErrorResponseParcel>(Commander::CommanderErrorKind::Ok);
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderAddJobRequest& request)
{
    coreContext_->get_scenes().access_read(request.get_scene_id(),
    [this, &request](const Scene& scene)
    {
        auto jobSurfaceWidth = static_cast<uint16_t>(scene.get_width() * request.get_scale());
        auto jobSurfaceHeight =  static_cast<uint16_t>(scene.get_height() * request.get_scale());
        log_debug(LOG_PREFIX, "Job for scene ", request.get_scene_id(), " added. Scene size: ",
            jobSurfaceWidth, "x", jobSurfaceHeight);
        coreContext_->get_jobs().add(
                Job { request.get_scene_id(), jobSurfaceWidth, jobSurfaceHeight, DEFAULT_CHUNK_SIZE });
    });

    return std::make_unique<CommanderErrorResponseParcel>(Commander::CommanderErrorKind::Ok);
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderGetNodeListRequest&)
{
    std::vector<Commander::Node> nodes;

    coreContext_->get_nodes().iterate_const([this, &nodes](uint32_t id, const Node& node)
    {
        nodes.emplace_back(Commander::Node {
                id,
                std::string("Node #").append(std::to_string(id)),
                node.get_state()
        });
    });

    return std::make_unique<CommanderGetNodeListResponseParcel>(std::move(nodes));
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderGetNodeInfoRequest& request)
{
    std::vector<PropertyPair> properties;

    coreContext_->get_nodes().access_read(request.get_node_id(), [&properties](const Node& node)
    {
        for (const auto& property : node.get_all_properties())
        {
            properties.emplace_back(PropertyPair {property.first, property.second});
        }
    });

    return std::make_unique<CommanderGetNodeInfoResponseParcel>(request.get_node_id(), std::move(properties));
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderSetNodeStateRequest& request)
{
    coreContext_->get_nodes().access_write(request.get_node_id(),
    [&request](Node& node)
    {
        node.set_state(request.get_node_state());
    });

    return std::make_unique<CommanderErrorResponseParcel>(Commander::CommanderErrorKind::Ok);
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderGetServerStatusRequest&)
{
    return std::make_unique<CommanderGetServerStatusResponseParcel>(
            coreContext_->get_scenes().get_last_modified(),
            coreContext_->get_jobs().get_last_modified(),
            coreContext_->get_nodes().get_last_modified());
}
