#pragma once

#include "ICommander.h"

#include <memory>
#include <atomic>

namespace Dcdr::Gui
{
    class IMainFormView;

    class Commander : public ICommander
    {
    public:
        explicit Commander(std::shared_ptr<IMainFormView> view);

        void send_job_control(uint32_t id, Interconnect::Commander::JobState state);
        void send_node_control(uint32_t id, Interconnect::Commander::NodeState state);

        void add_job(uint32_t sceneId, uint16_t width, uint16_t height);

        void select_job(uint32_t id);
        void select_node(uint32_t id);

        void request_terminate() override;

        void run();
    private:
        std::shared_ptr<IMainFormView> view_;
        std::atomic<bool> terminateRequested_;
    };
}