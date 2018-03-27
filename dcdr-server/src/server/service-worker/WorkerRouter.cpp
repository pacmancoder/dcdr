#include <dcdr/server/service-worker/WorkerRouter.h>

#include <dcdr/messaging/worker/WorkerRequestParcels.h>
#include <dcdr/messaging/worker/WorkerResponseParcels.h>

#include <dcdr/server/ServerExceptions.h>

#include <dcdr/logging/Logger.h>

using namespace Dcdr::Server;
using namespace Dcdr::Interconnect;
using namespace Dcdr::Logging;

WorkerRouter::WorkerRouter(const std::shared_ptr<CoreContext> &coreContext) :
        connectionId_(coreContext->get_connections().add(Connection())),
        coreContext_(coreContext) {}

WorkerRouter::~WorkerRouter()
{
    try
    {
        coreContext_->get_connections().remove(connectionId_);
    }
    catch (const std::exception& e)
    {
        log_error(std::string("Error during Worker router removal: ").append(e.what()));
    }
}

uint32_t WorkerRouter::get_connection_id()
{
    return connectionId_;
}


IParcel::ParcelPtr WorkerRouter::dispatch(const Dcdr::Interconnect::AWorkerRequestParcel &parcel)
{
    return parcel.dispatch(static_cast<IWorkerRequestDispatcher&>(*this));
}

IParcel::ParcelPtr WorkerRouter::dispatch(const WorkerLoginRequest&)
{
    auto nodeId = coreContext_->get_nodes().add(Node());

    coreContext_->get_connections().access_write(connectionId_,
    [nodeId](Connection& connection) {
        connection.attach_node(nodeId);
    });

    return std::make_unique<WorkerLoginResponseParcel>(nodeId);
}

IParcel::ParcelPtr WorkerRouter::dispatch(const WorkerLogoutRequest &request)
{
    coreContext_->get_nodes().remove(request.get_node_id());

    return nullptr;
}

IParcel::ParcelPtr WorkerRouter::dispatch(const WorkerSendHardwareInfoRequest &request)
{
    coreContext_->get_nodes().access_write(request.get_node_id(),
    [&request](Node& node)
    {
        for (const auto& property : request.get_properties())
        {
            node.set_property(property.name, property.value);
        }
    });

    return nullptr;
}

IParcel::ParcelPtr WorkerRouter::dispatch(const WorkerPollTasksRequest &request)
{
    std::vector<Worker::TaskInfo> tasks;

    coreContext_->get_jobs().iterate(
    [this, &request, &tasks](uint32_t jobId, Job& job)
    {
        const size_t CHUNKS_PER_NODE = 3;
        const uint32_t MIN_SAMPLES = 128;
        const uint32_t MAX_SAMPLES = 1024;

        for (size_t i = 0; i < CHUNKS_PER_NODE; ++i)
        {
            auto chunkTask = ChunkTask {
                    jobId,
                    request.get_node_id(),
                    job.get_surface().next_chunk_to_render(),
                    MIN_SAMPLES,
                    MAX_SAMPLES
            };

            // for each job create task
            uint32_t taskId = coreContext_->get_tasks().add(ChunkTask(chunkTask));

            tasks.push_back(
                    Worker::TaskInfo {
                            taskId,

                            jobId,

                            chunkTask.get_chunk_rect().x,
                            chunkTask.get_chunk_rect().y,
                            chunkTask.get_chunk_rect().w,
                            chunkTask.get_chunk_rect().h,

                            chunkTask.get_min_iterations(),
                            chunkTask.get_max_iterations()
                    });
        }
    });

    return std::make_unique<WorkerPollTasksResponseParcel>(request.get_node_id(), tasks);
}

IParcel::ParcelPtr WorkerRouter::dispatch(const WorkerGetSceneInfoRequest &request)
{
    uint16_t width = 0;
    uint16_t height = 0;
    std::string fileName;
    uint32_t sceneId = 0;

    // todo: rename scene_id to job id
    coreContext_->get_jobs().access_read(request.get_scene_id(),
    [this, &width, &height, &fileName, &sceneId](const Job& job)
    {
        width = job.get_width();
        height = job.get_height();
        sceneId = job.get_scene_id();

        coreContext_->get_scenes().access_read(job.get_scene_id(),
        [&fileName](const Scene& scene)
        {
            fileName = scene.get_scene_file_name();
        });
    });

    return std::make_unique<WorkerGetSceneInfoResponseParcel>(
            request.get_node_id(),
            sceneId,

            width,
            height,

            fileName);
}

IParcel::ParcelPtr WorkerRouter::dispatch(const WorkerCommitTasksRequest &request)
{
    for (const auto& artifact : request.get_artifacts())
    {
        uint32_t jobId = 0;
        ChunkRect chunkRect = {};

        coreContext_->get_tasks().access_read(artifact.taskId,
        [&jobId, &chunkRect](const ChunkTask& task)
        {
            jobId = task.get_job_id();
            chunkRect = task.get_chunk_rect();
        });

        coreContext_->get_jobs().access_write(jobId,
        [&chunkRect, &artifact](Job& job)
        {
            job.get_surface().commit_chunk(Chunk(chunkRect, artifact.data));
        });
    }

    return std::make_unique<WorkerServerStatusResponseParcel>(
            request.get_node_id(), Worker::ServerStatus::Ok);
}

IParcel::ParcelPtr WorkerRouter::dispatch(const WorkerDownloadSceneRequest &request)
{
    static const uint32_t SCENE_PART_SIZE = 1024;

    uint32_t sceneFileId = 0;

    std::vector<uint8_t> data;
    uint64_t sceneSize = 0;

    coreContext_->get_scenes().access_write(request.get_scene_id(),
    [&sceneFileId](Scene& scene)
    {
        sceneFileId = scene.get_scene_file_id();
    });

    coreContext_->get_shared_files().access_read(sceneFileId,
    [&data, &sceneSize, offset = request.get_offset()](const SharedFile& sharedFile)
    {
       data = sharedFile.read(SCENE_PART_SIZE, offset);
       sceneSize = sharedFile.size();
    });

    return std::make_unique<WorkerDownloadSceneResponseParcel>(
            request.get_node_id(),
            request.get_scene_id(),
            request.get_offset(),
            (request.get_offset() + data.size() < sceneSize) ?
                sceneSize - request.get_offset() - data.size() : 0,
            std::move(data));
}
