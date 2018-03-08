#pragma once

#include "ICommander.h"

#include <memory>
#include <atomic>

#include <dcdr/transport/ISyncClientTransport.h>

namespace Dcdr::Gui
{
    class IMainFormView;

    class CommanderNode : public ICommander
    {
    public:
        explicit CommanderNode(std::shared_ptr<IMainFormView> view);
        ~CommanderNode();


        void send_job_control(uint32_t id, Interconnect::Commander::JobState state);
        void send_node_control(uint32_t id, Interconnect::Commander::NodeState state);

        void add_job(uint32_t sceneId, float scale);

        void select_job(uint32_t id);
        void select_node(uint32_t id);

        void request_terminate() override;

        void run();

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}