#include "Commander.h"

#include <dcdr/utils/Timer.h>

#include <dcdr/logging/Logger.h>

#include <dcdr/transport/WebsocketSyncClientTransport.h>

#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelDeserializer.h>

#include <dcdr/messaging/IParcelDispatcher.h>
#include <dcdr/messaging/IParcel.h>

#include <dcdr/messaging/commander/CommanderRequestParcels.h>
#include <dcdr/messaging/commander/CommanderResponseParcels.h>

#include <chrono>
#include <thread>
#include <vector>
#include <functional>

#include "IMainFormView.h"

using namespace Dcdr::Gui;
using namespace Dcdr;
using namespace Dcdr::Transport;
using namespace Dcdr::Logging;

using namespace std::chrono_literals;

namespace
{

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
            InnerCommanderResponseDispatcher(VisitFunc visitFunc) :
                    visitFunc_(visitFunc) {}

            void dispatch(const ResponseType& parcel) override
            {
                visitFunc_(parcel);
            }

        private:
            VisitFunc visitFunc_;
        };

    public:
        CommanderResponseDispatcher(VisitFunc visitFunc) :
                innerDispatcher_(visitFunc) {}

        void dispatch(const Interconnect::ACommanderResponseParcel& parcel) override
        {
            parcel.dispatch(innerDispatcher_);
        }

    private:
        InnerCommanderResponseDispatcher innerDispatcher_;
    };
}

Commander::Commander(std::shared_ptr<IMainFormView> view) :
    view_(std::move(view)),
    transport_(std::make_unique<Transport::WebsocketSyncClientTransport>("127.0.0.1:61296", 10s)),
    terminateRequested_(false),
    scenesTimestamp_(0),
    nodesTimestamp_(0),
    jobsTimestamp_(0) {}

void Commander::run()
{
    Interconnect::FlatBuffersParcelSerializer parcelSerializer;
    Interconnect::FlatBuffersParcelDeserializer parcelDeserializer;

    Utils::Timer updateTimer(1s);

    while (!terminateRequested_)
    {
        if (updateTimer.elapsed())
        {
            auto serializedResponse = transport_->get_response(
                    parcelSerializer.serialize(Interconnect::CommanderGetServerStatusRequestParcel()));

            parcelDeserializer.deserialize(*serializedResponse)->dispatch(
                    CommanderResponseDispatcher<Interconnect::CommanderGetServerStatusResponse>(
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
                    ));
            updateTimer.reset();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    view_->terminate();
}

void Commander::request_terminate()
{
    terminateRequested_ = true;
}

void Commander::send_job_control(uint32_t id, Dcdr::Interconnect::Commander::JobState state)
{
    Interconnect::FlatBuffersParcelSerializer parcelSerializer;

    transport_->send_request(parcelSerializer.serialize(Interconnect::CommanderSetJobStateRequestParcel(id, state)));
}

void Commander::send_node_control(uint32_t id, Dcdr::Interconnect::Commander::NodeState state)
{
    Interconnect::FlatBuffersParcelSerializer parcelSerializer;

    transport_->send_request(parcelSerializer.serialize(Interconnect::CommanderSetNodeStateRequestParcel(id, state)));
}

void Commander::add_job(uint32_t sceneId, float scale)
{
    Interconnect::FlatBuffersParcelSerializer parcelSerializer;

    transport_->send_request(parcelSerializer.serialize(Interconnect::CommanderAddJobRequestParcel(sceneId, scale)));
}

void Commander::select_job(uint32_t id)
{
    Interconnect::FlatBuffersParcelSerializer parcelSerializer;
    Interconnect::FlatBuffersParcelDeserializer parcelDeserializer;

    auto serializedResponse = transport_->get_response(
            parcelSerializer.serialize(Interconnect::CommanderGetJobInfoRequestParcel(id)));

    parcelDeserializer.deserialize(*serializedResponse)->dispatch(
            CommanderResponseDispatcher<Interconnect::CommanderGetJobInfoResponse>(
                    [this](const Interconnect::CommanderGetJobInfoResponse& response)
                    {
                        view_->clear_job_info();
                        for (const auto& property : response.get_job_info())
                        {
                            view_->add_job_info(property.name, property.value);
                        }
                    }
            ));

}

void Commander::select_node(uint32_t id)
{
    Interconnect::FlatBuffersParcelSerializer parcelSerializer;
    Interconnect::FlatBuffersParcelDeserializer parcelDeserializer;

    auto serializedResponse = transport_->get_response(
            parcelSerializer.serialize(Interconnect::CommanderGetNodeInfoRequestParcel(id)));

    parcelDeserializer.deserialize(*serializedResponse)->dispatch(
            CommanderResponseDispatcher<Interconnect::CommanderGetNodeInfoResponse>(
                    [this](const Interconnect::CommanderGetNodeInfoResponse& response)
                    {
                        view_->clear_node_info();
                        for (const auto& property : response.get_node_info())
                        {
                            view_->add_node_info(property.name, property.value);
                        }
                    }
            ));
}

void Commander::update_node_list()
{
    Interconnect::FlatBuffersParcelSerializer parcelSerializer;
    Interconnect::FlatBuffersParcelDeserializer parcelDeserializer;


    auto serializedResponse = transport_->get_response(
            parcelSerializer.serialize(Interconnect::CommanderGetNodeListRequestParcel()));

    parcelDeserializer.deserialize(*serializedResponse)->dispatch(
            CommanderResponseDispatcher<Interconnect::CommanderGetNodeListResponse>(
                    [this](const Interconnect::CommanderGetNodeListResponse& response)
                    {
                        view_->clear_nodes();
                        for (const auto& node : response.get_nodes())
                        {
                            view_->add_node(node.id, node.name, node.state);
                        }
                    }
            ));
}

void Commander::update_job_list()
{
    Interconnect::FlatBuffersParcelSerializer parcelSerializer;
    Interconnect::FlatBuffersParcelDeserializer parcelDeserializer;

    auto serializedResponse = transport_->get_response(
            parcelSerializer.serialize(Interconnect::CommanderGetJobListRequestParcel()));

    parcelDeserializer.deserialize(*serializedResponse)->dispatch(
            CommanderResponseDispatcher<Interconnect::CommanderGetJobListResponse>(
                    [this](const Interconnect::CommanderGetJobListResponse& response)
                    {
                        view_->clear_jobs();
                        for (const auto& job : response.get_jobs())
                        {
                            view_->add_job(job.id, job.name, job.state);
                        }
                    }
            ));
}

void Commander::update_scene_list()
{
    Interconnect::FlatBuffersParcelSerializer parcelSerializer;
    Interconnect::FlatBuffersParcelDeserializer parcelDeserializer;

    auto serializedResponse = transport_->get_response(
            parcelSerializer.serialize(Interconnect::CommanderGetSceneListRequestParcel()));

    parcelDeserializer.deserialize(*serializedResponse)->dispatch(
            CommanderResponseDispatcher<Interconnect::CommanderGetSceneListResponse>(
                    [this](const Interconnect::CommanderGetSceneListResponse& response)
                    {
                        view_->clear_scenes();
                        for (const auto& scene : response.get_scenes())
                        {
                            view_->add_scene(scene.id, scene.name, scene.width, scene.height);
                        }
                    }
            ));
}
