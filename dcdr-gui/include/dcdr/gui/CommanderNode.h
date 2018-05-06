#pragma once

#include <dcdr/gui/ICommander.h>

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


        void send_job_control(Interconnect::Commander::JobState state) override;
        void send_node_control(Interconnect::Commander::NodeState state) override;

        void add_job(uint32_t sceneId, float scale) override;

        void select_job(uint32_t id) override;
        void select_node(uint32_t id) override;

        void request_terminate() override;

        void run();

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}