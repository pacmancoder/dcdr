#include "Commander.h"

#include <dcdr/logging/Logger.h>

#include <dcdr/transport/TcpSyncClientTransport.h>

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


    const std::array<Scene, 2> scenes = {
            Scene {"Cornell", 640, 480},
            Scene {"Spheres", 1024, 768}
    };

    std::vector<Job> jobs;

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
    view_(std::move(view)), terminateRequested_(false) {}

void Commander::run()
{
    TcpSyncClientTransport transport("127.0.0.1:1206", 10s);

    Interconnect::FlatBuffersParcelSerializer parcelSerializer;
    Interconnect::FlatBuffersParcelDeserializer parcelDeserializer;

    auto serializedResponse = transport.get_response(parcelSerializer.serialize(Interconnect::CommanderGetSceneListRequestParcel()));
    parcelDeserializer.deserialize(*serializedResponse)->dispatch(CommanderResponseDispatcher<Interconnect::CommanderGetSceneListResponse>(
    [this](const Interconnect::CommanderGetSceneListResponse& response)
    {
        log_info("Got scenes. sending to gui...");
        for (const auto& scene : response.get_scenes())
        {
            log_info("Sending scene...");
            view_->add_scene(scene.id, scene.name, scene.width, scene.height);
        }

    }));

    uint32_t i = 0;
    for (const auto& scene : scenes)
    {
        view_->add_scene(i++, scene.name, scene.width, scene.height);
    }

    view_->add_node(0, "Test Node", Interconnect::Commander::NodeState::Offline);
    view_->add_node(1, "Active", Interconnect::Commander::NodeState::Active);


    while (!terminateRequested_) { std::this_thread::sleep_for(std::chrono::milliseconds(100)); }
    view_->terminate();
}

void Commander::request_terminate()
{
    terminateRequested_ = true;
}

void Commander::send_job_control(uint32_t /*id*/, Dcdr::Interconnect::Commander::JobState /*state*/)
{

}

void Commander::send_node_control(uint32_t /*id*/, Dcdr::Interconnect::Commander::NodeState /*state*/)
{

}

void Commander::add_job(uint32_t sceneId, uint16_t width, uint16_t height)
{
    jobs.push_back(Job {uint32_t(jobs.size()), scenes[sceneId].name + " " + std::to_string(width) + "x" + std::to_string(height), width, height});
    view_->clear_jobs();
    for (auto& job : jobs)
    {
        view_->add_job(job.id, job.name, Interconnect::Commander::JobState::InProgress);
    }
}

void Commander::select_job(uint32_t id)
{
    view_->clear_job_info();
    view_->add_job_info("job", std::to_string(id));
}

void Commander::select_node(uint32_t /*id*/)
{

}
