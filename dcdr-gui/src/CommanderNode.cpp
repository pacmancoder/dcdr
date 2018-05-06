#include <dcdr/gui/CommanderNode.h>

#include <dcdr/utils/Timer.h>

#include <dcdr/logging/Logger.h>

#include <dcdr/transport/WebsocketSyncClientTransport.h>

#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelDeserializer.h>

#include <dcdr/messaging/IParcelDispatcher.h>
#include <dcdr/messaging/IParcel.h>

#include <dcdr/messaging/commander/CommanderRequestParcels.h>
#include <dcdr/messaging/commander/CommanderResponseParcels.h>

#include <dcdr/gui/CommanderExceptions.h>
#include <dcdr/gui/IMainFormView.h>

#include <chrono>
#include <thread>
#include <vector>
#include <functional>
#include <optional>

using namespace Dcdr;
using namespace Dcdr::Gui;
using namespace Dcdr::Transport;
using namespace Dcdr::Logging;
using namespace Dcdr::Interconnect;


using namespace std::chrono_literals;

namespace
{
    const char* LOG_PREFIX = "[GUI][CommanderNode] ";
    struct Scene
    {
        std::string name;
        uint16_t width;
        uint16_t height;
    };

    struct Job
    {
        uint32_t id;
        std::string name;
        uint16_t width;
        uint16_t height;
    };

    // ===========

    template<typename ResponseType>
    class CommanderResponseDispatcher : public Interconnect::IParcelDispatcher
    {
    public:
        using VisitFunc = std::function<void(const ResponseType&)>;

    private:
        class InnerCommanderResponseDispatcher : public Interconnect::ICommanderResponseDispatcher
        {
        public:
            explicit InnerCommanderResponseDispatcher(VisitFunc visitFunc) :
                    visitFunc_(visitFunc) {}

            void dispatch(const ResponseType& parcel) override
            {
                visitFunc_(parcel);
            }

        private:
            VisitFunc visitFunc_;
        };

    public:
        explicit CommanderResponseDispatcher(VisitFunc visitFunc) :
                innerDispatcher_(visitFunc) {}

        void dispatch(const Interconnect::ACommanderResponseParcel& parcel) override
        {
            parcel.dispatch(innerDispatcher_);
        }

    private:
        InnerCommanderResponseDispatcher innerDispatcher_;
    };
}

struct CommanderNode::Impl
{
    explicit Impl(std::shared_ptr<IMainFormView> view);

    std::shared_ptr<IMainFormView> view_;
    std::unique_ptr<Transport::ISyncClientTransport>  transport_;
    std::atomic<bool> terminateRequested_;

    uint64_t scenesTimestamp_;
    uint64_t nodesTimestamp_;
    uint64_t jobsTimestamp_;

    FlatBuffersParcelSerializer serializer_;
    FlatBuffersParcelDeserializer deserializer_;

    std::optional<uint32_t> currentScene_;
    std::optional<uint32_t> currentNode_;

    void run();

    void update_node_list();
    void update_job_list();
    void update_scene_list();

    template<class ResponseType, class RequestParcelType, typename ResponseVisitFunc>
    void perform_command(RequestParcelType&& request, ResponseVisitFunc&& func);
};

CommanderNode::Impl::Impl(std::shared_ptr<IMainFormView> view) :
    view_(std::move(view)),
    transport_(std::make_unique<Transport::WebsocketSyncClientTransport>("127.0.0.1:61296", 10s)),
    terminateRequested_(false),
    scenesTimestamp_(0),
    nodesTimestamp_(0),
    jobsTimestamp_(0),
    serializer_(),
    deserializer_(),
    currentScene_(std::nullopt),
    currentNode_(std::nullopt) {}

CommanderNode::~CommanderNode() = default;

template<class ResponseType, class RequestParcelType, typename ResponseVisitFunc>
void CommanderNode::Impl::perform_command(RequestParcelType&& request, ResponseVisitFunc&& func)
{
    static_assert(std::is_base_of<ACommanderRequestParcel, RequestParcelType>::value,
                  "Request type should have a base of AWorkerRequestParcel type");
    // TODO: make pseudo base class
    //static_assert(std::is_base_of<WorkerResponse, ResponseType>::value,
    //             "Request type should have a base of AWorkerRequest type");

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

    CommanderResponseDispatcher<ResponseType> responseDispatcher(std::forward<ResponseVisitFunc>(func));

    response->dispatch(responseDispatcher);
}


CommanderNode::CommanderNode(std::shared_ptr<IMainFormView> view) :
    impl_(std::make_unique<Impl>(view)) {}

void CommanderNode::run()
{
    impl_->run();
}

void CommanderNode::Impl::run()
{
    Utils::Timer updateTimer(1s);
    Utils::Timer surfaceUpdateTimer(2s);

    while (!terminateRequested_)
    {
        if (updateTimer.elapsed())
        {
            perform_command<CommanderGetServerStatusResponse>(
                    CommanderGetServerStatusRequestParcel(),
                    [this](const Interconnect::CommanderGetServerStatusResponse& response)
                    {
                        if (response.get_nodes_last_modified_timestamp() > nodesTimestamp_)
                        {
                            update_node_list();
                            nodesTimestamp_ = response.get_nodes_last_modified_timestamp();
                        }
                        if (response.get_jobs_last_modified_timestamp() > jobsTimestamp_)
                        {
                            update_job_list();
                            jobsTimestamp_ = response.get_jobs_last_modified_timestamp();
                        }
                        if (response.get_scenes_last_modified_timestamp() > scenesTimestamp_)
                        {
                            update_scene_list();
                            scenesTimestamp_ = response.get_scenes_last_modified_timestamp();
                        }
                    }
            );

            updateTimer.reset();
        }
        if (surfaceUpdateTimer.elapsed() && currentScene_.has_value())
        {
            perform_command<CommanderGetJobArtifactResponse>(
                    CommanderGetJobArtifactRequestParcel(
                        currentScene_.value(), uint8_t(0), Commander::ArtifactFormat::Rgb24Unsigned
                    ),
                    [this](const CommanderGetJobArtifactResponse& response)
                    {
                        if (response.get_format() != Commander::ArtifactFormat::Rgb24Unsigned)
                        {
                            log_error(LOG_PREFIX, "Not supported artifact format!");
                            return;
                        }

                        view_->display_preview(
                                response.get_width(), response.get_height(), response.get_data().data());
                    }
            );

            surfaceUpdateTimer.reset();
        }

        std::this_thread::sleep_for(100ms);
    }
    view_->terminate();
}

void CommanderNode::request_terminate()
{
    impl_->terminateRequested_ = true;
}

void CommanderNode::send_job_control(Dcdr::Interconnect::Commander::JobState state)
{
    if (impl_->currentScene_ == std::nullopt)
    {

        log_warning(LOG_PREFIX, "No scene selected! Can't change the state.");
        return;
    }

    impl_->perform_command<CommanderErrorResponse>(
            CommanderSetJobStateRequestParcel(impl_->currentScene_.value(), state),
            [this, state](const CommanderErrorResponse& response)
            {
                if (response.get_error_kind() != Interconnect::Commander::CommanderErrorKind::Ok)
                {
                    log_error(LOG_PREFIX, "Can't set job state for job with id ", impl_->currentScene_.value());
                    impl_->view_->show_error("Can't set new job state");
                    return;
                }

                if (state == Dcdr::Interconnect::Commander::JobState::Removed)
                {
                    impl_->currentScene_ = std::nullopt;
                }
            });
}

void CommanderNode::send_node_control(Dcdr::Interconnect::Commander::NodeState state)
{
    if (impl_->currentNode_ == std::nullopt)
    {
        log_warning(LOG_PREFIX, "No node selected! Can't change the state.");
        return;
    }

    impl_->perform_command<CommanderErrorResponse>(
            CommanderSetNodeStateRequestParcel(impl_->currentNode_.value(), state),
            [this, state](const CommanderErrorResponse& response)
            {
                if (response.get_error_kind() != Interconnect::Commander::CommanderErrorKind::Ok)
                {
                    log_error(LOG_PREFIX, "Can't set node state for node with id ", impl_->currentNode_.value());
                    impl_->view_->show_error("Can't set new node state");
                    return;
                }

                if (state == Dcdr::Interconnect::Commander::NodeState::Offline)
                {
                    impl_->currentNode_ = std::nullopt;
                }
            });
}

void CommanderNode::add_job(uint32_t sceneId, float scale)
{
    impl_->perform_command<CommanderErrorResponse>(
            CommanderAddJobRequestParcel(sceneId, scale),
            [this, sceneId, scale](const CommanderErrorResponse& response)
            {
                if (response.get_error_kind() != Interconnect::Commander::CommanderErrorKind::Ok)
                {
                    log_error(LOG_PREFIX, "Can't add job with sceneId  ", sceneId, " and scale ", scale);
                    impl_->view_->show_error("Can't create new job");
                }
            });

}

void CommanderNode::select_job(uint32_t id)
{
    log_warning(LOG_PREFIX, "Selected scene ", id);
    impl_->currentScene_ = id;

    impl_->perform_command<CommanderGetJobInfoResponse>(
            CommanderGetJobInfoRequestParcel(id),
            [this, id](const CommanderGetJobInfoResponse& response)
            {
                impl_->view_->clear_job_info();
                for (const auto& property : response.get_job_info())
                {
                    impl_->view_->add_job_info(property.name, property.value);
                }
            });
}

void CommanderNode::select_node(uint32_t id)
{
    impl_->currentNode_ = id;

    impl_->perform_command<CommanderGetNodeInfoResponse>(
            CommanderGetNodeInfoRequestParcel(id),
            [this, id](const CommanderGetNodeInfoResponse& response)
            {
                impl_->view_->clear_node_info();
                for (const auto& property : response.get_node_info())
                {
                    impl_->view_->add_node_info(property.name, property.value);
                }
            });
}

void CommanderNode::Impl::update_node_list()
{
    perform_command<CommanderGetNodeListResponse>(
            CommanderGetNodeListRequestParcel(),
            [this](const CommanderGetNodeListResponse& response)
            {
                view_->clear_nodes();
                for (const auto& node : response.get_nodes())
                {
                    view_->add_node(node.id, node.name, node.state);
                }
            });
}

void CommanderNode::Impl::update_job_list()
{
    perform_command<CommanderGetJobListResponse>(
            CommanderGetJobListRequestParcel(),
            [this](const CommanderGetJobListResponse& response)
            {
                view_->clear_jobs();
                for (const auto& job : response.get_jobs())
                {
                    view_->add_job(job.id, job.name, job.state);
                    log_warning(LOG_PREFIX, "Added job ", job.name);
                }
            });
}

void CommanderNode::Impl::update_scene_list()
{
    perform_command<CommanderGetSceneListResponse>(
            CommanderGetSceneListRequestParcel(),
            [this](const CommanderGetSceneListResponse& response)
            {
                view_->clear_scenes();
                for (const auto& scene : response.get_scenes())
                {
                    view_->add_scene(scene.id, scene.name, scene.width, scene.height);
                }
            });
}