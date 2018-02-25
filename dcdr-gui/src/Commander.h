#pragma once

#include "ICommander.h"

#include <memory>
#include <atomic>

#include <dcdr/transport/ISyncClientTransport.h>

namespace Dcdr::Gui
{
    class IMainFormView;

    class Commander : public ICommander
    {
    public:
        explicit Commander(std::shared_ptr<IMainFormView> view);

        void send_job_control(uint32_t id, Interconnect::Commander::JobState state);
        void send_node_control(uint32_t id, Interconnect::Commander::NodeState state);

        void add_job(uint32_t sceneId, float scale);

        void select_job(uint32_t id);
        void select_node(uint32_t id);

        void request_terminate() override;

        void run();
        // TODO: Pimpl
    private:
        void update_node_list();
        void update_job_list();
        void update_scene_list();
    private:
        std::shared_ptr<IMainFormView> view_;
        std::unique_ptr<Transport::ISyncClientTransport>  transport_;
        std::atomic<bool> terminateRequested_;

        uint64_t scenesTimestamp_;
        uint64_t nodesTimestamp_;
        uint64_t jobsTimestamp_;
    };
}