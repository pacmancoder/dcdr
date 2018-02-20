#include <dcdr/server/service-commander/CommanderRouter.h>

#include <dcdr/messaging/commander/CommanderRequestParcels.h>
#include <dcdr/messaging/commander/CommanderResponseParcels.h>

#include <string>

using namespace Dcdr::Server;
using namespace Dcdr::Interconnect;

CommanderRouter::CommanderRouter(std::shared_ptr<CoreContext> coreContext) :
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
        scenes.emplace_back(Commander::Scene{id, scene.get_name(), scene.get_width(), scene.get_height()});
    });

    return std::make_unique<CommanderGetSceneListReponseParcel>(std::move(scenes));
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderGetJobListRequest&)
{
    std::vector<Commander::Job> jobs;

    coreContext_->get_jobs().iterate_const([this, &jobs](uint32_t id, const Job& job)
    {
        std::string sceneName = coreContext_->get_scenes().read(job.get_scene_id())->get_name();
        sceneName.append(" (")
                 .append(std::to_string(job.get_width()))
                 .append("x")
                 .append(std::to_string(job.get_height()))
                 .append(")");


        jobs.emplace_back(Commander::Job{
               id,
               sceneName,
               job.get_state()});
    });

    return std::make_unique<CommanderGetJobListResponseParcel>(std::move(jobs));
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderGetJobInfoRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderGetJobArtifactRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderSetJobStateRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderAddJobRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderGetNodeListRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderGetNodeInfoRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderSetNodeStateRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}

IParcel::ParcelPtr CommanderRouter::dispatch(const CommanderGetServerStatusRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}
