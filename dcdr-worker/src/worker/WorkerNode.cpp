#include <dcdr/worker/WorkerNode.h>

#include <dcdr/worker/WorkerExceptions.h>

#include <dcdr/logging/Logger.h>
#include <dcdr/transport/WebsocketSyncClientTransport.h>

#include <dcdr/messaging/IParcelDispatcher.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelDeserializer.h>


#include <dcdr/messaging/worker/WorkerRequestParcels.h>
#include <dcdr/messaging/worker/WorkerResponseParcels.h>

#include <dcdr/messaging/worker/WorkerInterconnectTypes.h>

#include <dcdr/worker/SceneStorage.h>
#include <dcdr/worker/SceneLoader.h>

#include <mcrt/SurfaceRenderer.h>

#include <iostream>
#include <fstream>
#include <type_traits>
#include <future>

using namespace Dcdr;
using namespace Dcdr::Worker;
using namespace Dcdr::Logging;
using namespace Dcdr::Interconnect;
using namespace Dcdr::Transport;

using namespace std::chrono_literals;

namespace
{
    const char* LOG_PREFIX = "[Worker][WorkerNode] ";

    template<typename ResponseType>
    class WorkerResponseDispatcher : public IParcelDispatcher
    {
    public:
        using VisitFunc = std::function<void(const ResponseType&)>;

    private:
        class InnerWorkerResponseDispatcher : public IWorkerResponseDispatcher
        {
        public:
            explicit InnerWorkerResponseDispatcher(VisitFunc visitFunc) :
                    visitFunc_(visitFunc) {}

            void dispatch(const ResponseType& parcel) override
            {
                visitFunc_(parcel);
            }

        private:
            VisitFunc visitFunc_;
        };

    public:
        explicit WorkerResponseDispatcher(VisitFunc visitFunc) :
                innerDispatcher_(visitFunc) {}

        void dispatch(const AWorkerResponseParcel& parcel) override
        {
            parcel.dispatch(innerDispatcher_);
        }

    private:
        InnerWorkerResponseDispatcher innerDispatcher_;
    };
}

struct WorkerNode::Impl
{
    explicit Impl(
            const std::string& sceneCache,
            const std::string& ip,
            const std::string& port);

    void run();

    template<class ResponseType, class RequestParcelType, typename ResponseVisitFunc>
    void perform_command(RequestParcelType&& request, ResponseVisitFunc&& func);

    void load_scene(const WorkerGetSceneInfoResponse& sceneInfo, uint32_t taskId);

private:
    std::unique_ptr<WebsocketSyncClientTransport> transport_;

    FlatBuffersParcelDeserializer deserializer_;
    FlatBuffersParcelSerializer serializer_;


    std::string tmpPath_;
    SceneStorage sceneStorage_;
    std::map<uint32_t, Mcrt::Scene> scenes_;

    uint32_t nodeId_;

    std::string ip_;
    std::string port_;
};

WorkerNode::WorkerNode(const Utils::ArgsParser& args) :
        impl_(std::make_unique<Impl>(
                args.get_argument("scene-cache", ""),
                args.get_argument("ip", "127.0.0.1"),
                args.get_argument("port", "61297"))) {}

WorkerNode::~WorkerNode() = default;


WorkerNode::Impl::Impl(
        const std::string& sceneCache,
        const std::string& ip,
        const std::string& port) :
    transport_(nullptr),
    deserializer_(),
    serializer_(),
    tmpPath_(sceneCache),
    sceneStorage_(sceneCache),
    scenes_(),
    nodeId_(0),
    ip_(ip),
    port_(port) {}

template<class ResponseType, class RequestParcelType, typename ResponseVisitFunc>
void WorkerNode::Impl::perform_command(RequestParcelType&& request, ResponseVisitFunc&& func)
{
    static_assert(std::is_base_of<AWorkerRequestParcel, RequestParcelType>::value,
                  "Request type should have a base of AWorkerRequestParcel type");
    static_assert(std::is_base_of<WorkerResponse, ResponseType>::value,
                  "Request type should have a base of AWorkerRequest type");

    auto serializedRequest = std::forward<IParcel>(request).serialize(serializer_);

    if (serializedRequest.empty())
    {
        return;
    }

    auto serializedResponse = transport_->get_response(serializedRequest);

    if (serializedResponse == nullptr)
    {
        throw EmptyResponseException("Response is empty");
    }

    auto response = deserializer_.deserialize(*serializedResponse);

    WorkerResponseDispatcher<ResponseType> responseDispatcher(std::forward<ResponseVisitFunc>(func));

    response->dispatch(responseDispatcher);
}

void WorkerNode::Impl::load_scene(const WorkerGetSceneInfoResponse& sceneInfo, uint32_t taskId)
{
    auto scene = scenes_.emplace(taskId, Mcrt::Scene(sceneInfo.get_width(), sceneInfo.get_height()));

    if (!sceneStorage_.is_file_cached(sceneInfo.get_file_name()))
    {
        auto downloadHandle = sceneStorage_.cache_start(
                sceneInfo.get_file_name());

        uint64_t offset = 0;
        bool continueDownload = true;
        while (continueDownload)
        {
            perform_command<WorkerDownloadSceneResponse>(
                    WorkerDownloadSceneRequestParcel(nodeId_, sceneInfo.get_scene_id(), offset),
                    [this, downloadHandle, &offset, &continueDownload](const WorkerDownloadSceneResponse& part)
                    {

                        sceneStorage_.cache_write_chunk(downloadHandle, part.get_data());
                        offset += part.get_data().size();

                        if (part.get_bytes_left() == 0)
                        {
                            continueDownload = false;
                        }
                    });
        }

        sceneStorage_.cache_finish(downloadHandle);
    }

    SceneLoader loader(
            sceneStorage_.get_cached_file_path(sceneInfo.get_file_name()));

    loader.load_to(scene.first->second);


    log_info(LOG_PREFIX, "Scene #", scene.first->first, " loaded");
}

void WorkerNode::Impl::run()
{
    transport_ = std::make_unique<WebsocketSyncClientTransport>("127.0.0.1:61297", 10s);

    FlatBuffersParcelDeserializer deserializer;
    FlatBuffersParcelSerializer serializer;


    perform_command<WorkerLoginResponse>(
            WorkerLoginRequestParcel("Test_worker", "098f6bcd4621d373cade4e832627b4f6"),
            [this](const WorkerLoginResponse& response)
            {
                nodeId_ = response.get_node_id();
            });

    log_info(std::string("Logged in. Node id: ").append(std::to_string(nodeId_)));

    Mcrt::SurfaceRenderer surfaceRenderer;

    for(;;)
    {
        std::vector<Dcdr::Interconnect::Worker::TaskArtifact> artifacts;
        perform_command<WorkerPollTasksResponse>(
                WorkerPollTasksRequestParcel(nodeId_),
                [this, &artifacts, &surfaceRenderer](const WorkerPollTasksResponse& response)
                {
                    std::map<uint32_t, std::future<std::vector<Types::MultisamplePixel>>> asyncTasks;

                    for (const auto& task : response.get_tasks())
                    {
                        auto foundScene = scenes_.find(task.sceneId);
                        // check that scene is present in current run
                        if (foundScene == scenes_.cend())
                        {
                            perform_command<WorkerGetSceneInfoResponse>(
                                    WorkerGetSceneInfoRequestParcel(nodeId_, task.sceneId),
                                    [this, &task](const WorkerGetSceneInfoResponse &sceneInfo)
                                    {
                                        // todo: sceneId -> jobId
                                        load_scene(sceneInfo, task.sceneId);
                                    });
                        }

                        // actual rendering


                        asyncTasks.emplace(task.taskId, std::async(std::launch::async, [this, &surfaceRenderer, &task]()
                        {
                            auto& scene = scenes_.at(task.sceneId);

                            auto frameInfo = Mcrt::FrameInfo {scene.get_frame_width(), scene.get_frame_height()};
                            auto chunkInfo = Mcrt::ChunkInfo {task.x, task.y, task.width, task.height};

                            auto rawData = surfaceRenderer.RenderChunk(scene, frameInfo, chunkInfo);

                            auto multisamplePixels = std::vector<Types::MultisamplePixel>(rawData.size());
                            for (size_t i = 0; i < multisamplePixels.size(); ++i)
                            {
                                multisamplePixels[i].color =
                                        Types::Color(
                                                glm::clamp(rawData[i][0], 0.0f, 1.0f),
                                                glm::clamp(rawData[i][1], 0.0f, 1.0f),
                                                glm::clamp(rawData[i][2], 0.0f, 1.0f));
                                multisamplePixels[i].samples = 32;
                            }

                            return multisamplePixels;
                        }));
                    }

                    for (auto& asyncTask : asyncTasks)
                    {
                        artifacts.push_back(Dcdr::Interconnect::Worker::TaskArtifact
                        {
                            asyncTask.first, asyncTask.second.get()
                        });
                    }
                });

        perform_command<WorkerServerStatusResponse>(
                WorkerCommitTasksRequestParcel(nodeId_, std::move(artifacts)),
                [](const WorkerServerStatusResponse&)
                {
                });

        if (!std::cin.eof())
        {
            std::string value;

            std::cin >> value;
            if (value == "@exit")
            {
                break;
            }
        }
    }

    perform_command<WorkerServerStatusResponse>(
            WorkerLogoutRequestParcel(nodeId_),
            [](const WorkerServerStatusResponse&)
            {
                log_info(std::string("Logged out."));
            });
}

void WorkerNode::run()
{
    impl_->run();
}
