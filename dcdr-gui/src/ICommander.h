#pragma once

#include <dcdr/messaging/commander/CommanderInterconnectTypes.h>
#include <cstdint>

namespace Dcdr::Gui
{
    class ICommander
    {
    public:
        virtual void send_job_control(uint32_t id, Interconnect::Commander::JobState state) = 0;
        virtual void get_job_artifact(uint32_t id) = 0;
        virtual void add_job(uint32_t sceneId, uint16_t width, uint16_t height) = 0;

        virtual void set_node_state(uint32_t id, Interconnect::Commander::NodeState state) = 0;

        virtual void set_current_job(uint32_t id) = 0;
        virtual void set_current_node(uint32_t id) = 0;
    };
}