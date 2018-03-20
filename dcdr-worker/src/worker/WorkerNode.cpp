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

#include <dcdr/renderer/Scene.h>

#include <iostream>
#include <fstream>
#include <type_traits>

using namespace Dcdr;
using namespace Dcdr::Worker;
using namespace Dcdr::Logging;
using namespace Dcdr::Interconnect;
using namespace Dcdr::Transport;

using namespace std::chrono_literals;

namespace
{
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
    explicit Impl(const std::string& sceneCache = "");

    void run();

    template<class ResponseType, class RequestParcelType, typename ResponseVisitFunc>
    void perform_command(RequestParcelType&& request, ResponseVisitFunc&& func);

private:
    std::unique_ptr<WebsocketSyncClientTransport> transport_;

    FlatBuffersParcelDeserializer deserializer_;
    FlatBuffersParcelSerializer serializer_;


    std::string tmpPath_;
    SceneStorage sceneStorage_;
    std::map<uint32_t, Renderer::Scene> scenes_;
};

WorkerNode::WorkerNode(const Utils::ArgsParser& args) :
        impl_(std::make_unique<Impl>(args.get_argument("scene-cache"))) {}

WorkerNode::~WorkerNode() = default;


WorkerNode::Impl::Impl(const std::string& sceneCache) :
    transport_(nullptr),
    deserializer_(),
    serializer_(),
    tmpPath_(sceneCache),
    sceneStorage_(sceneCache),
    scenes_() {}

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


void WorkerNode::Impl::run()
{
    transport_ = std::make_unique<WebsocketSyncClientTransport>("127.0.0.1:61297", 10s);

    FlatBuffersParcelDeserializer deserializer;
    FlatBuffersParcelSerializer serializer;

    uint32_t nodeId = 0;

    perform_command<WorkerLoginResponse>(
            WorkerLoginRequestParcel("Test_worker", "098f6bcd4621d373cade4e832627b4f6"),
            [&nodeId](const WorkerLoginResponse& response)
            {
                nodeId = response.get_node_id();
            });

    log_info(std::string("Logged in. Node id: ").append(std::to_string(nodeId)));

    for(;;)
    {
        // TODO. [INFO] This hydra will be refactored. Just for testing
        std::vector<Dcdr::Interconnect::Worker::TaskArtifact> artifacts;
        perform_command<WorkerPollTasksResponse>(
                WorkerPollTasksRequestParcel(nodeId),
                [this, &artifacts, nodeId](const WorkerPollTasksResponse& response)
                {
                    for (const auto& task : response.get_tasks())
                    {
                        perform_command<WorkerGetSceneInfoResponse>(
                                WorkerGetSceneInfoRequestParcel(nodeId, task.sceneId),
                                [this, nodeId, &task](const WorkerGetSceneInfoResponse& sceneInfo)
                                {
                                    if (scenes_.find(sceneInfo.get_scene_id()) == scenes_.cend())
                                    {
                                        auto scene = scenes_.emplace(
                                                sceneInfo.get_scene_id(),
                                                Renderer::Scene(sceneInfo.get_width(), sceneInfo.get_height()));

                                        if (!sceneStorage_.is_file_cached(sceneInfo.get_file_name()))
                                        {
                                            auto downloadHandle = sceneStorage_.cache_start(
                                                    sceneInfo.get_file_name());

                                            uint64_t offset = 0;
                                            bool continueDownload = true;
                                            while (continueDownload)
                                            {
                                                perform_command<WorkerDownloadSceneResponse>(
                                                        WorkerDownloadSceneRequestParcel(nodeId, task.sceneId, offset),
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
                                            SceneLoader loader(
                                                    sceneStorage_.get_cached_file_path(sceneInfo.get_file_name()));
                                            loader.load_to(scene.first->second);
                                        }

                                        log_info("Scene id: ", scene.first->first);
                                    }
                                });

                        std::vector<Dcdr::Types::MultisamplePixel> pixels;
                        pixels.resize(task.width * task.height);
                        for (auto& pixel : pixels)
                        {
                            pixel.samples = 1;
                            pixel.color.r = 1.0;
                            pixel.color.g = 1.0;
                            pixel.color.b = 1.0;
                        }

                        artifacts.push_back(Dcdr::Interconnect::Worker::TaskArtifact
                        {
                            task.taskId,
                            std::move(pixels)
                        });
                    }
                });

        perform_command<WorkerServerStatusResponse>(
                WorkerCommitTasksRequestParcel(nodeId, std::move(artifacts)),
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
            WorkerLogoutRequestParcel(nodeId),
            [](const WorkerServerStatusResponse&)
            {
                log_info(std::string("Logged out."));
            });
}

void WorkerNode::run()
{
    try
    {
        impl_->run();
    }
    catch (std::exception e)
    {
        log_error(std::string("Error: ").append(e.what()));
    }
}
