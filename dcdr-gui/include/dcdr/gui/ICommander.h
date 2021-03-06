#pragma once

#include <dcdr/messaging/commander/CommanderInterconnectTypes.h>
#include <cstdint>

namespace Dcdr::Gui
{
    class ICommander
    {
    public:

        virtual void send_job_control(Interconnect::Commander::JobState state) = 0;
        virtual void send_node_control(Interconnect::Commander::NodeState state) = 0;

        virtual void add_job(uint32_t sceneId, float scale) = 0;

        virtual void select_job(uint32_t id) = 0;
        virtual void select_node(uint32_t id) = 0;

        virtual void request_terminate() = 0;
    };
}