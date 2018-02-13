#pragma once

#include <dcdr/messaging/commander/CommanderInterconnectTypes.h>
#include <cstdint>

namespace Dcdr::Gui
{
    class IMainFormView
    {
    public:
        virtual void clear_nodes() = 0;
        virtual void add_node(int id, const std::string& name, Interconnect::Commander::NodeState state) = 0;

        virtual void clear_node_info() = 0;
        virtual void add_node_info(const std::string& name, const std::string& value) = 0;

        virtual void clear_jobs() = 0;
        virtual void add_job(int id, const std::string& name, Interconnect::Commander::JobState) = 0;

        virtual void clear_scenes() = 0;
        virtual void add_scene(int id, const std::string& name, int width, int height) = 0;

        virtual void display_preview(uint16_t width, uint16_t height, const uint8_t* data) = 0;

        virtual void write_log_message(const std::string& name) = 0;
        virtual void show_error(const std::string& name) = 0;

        virtual void terminate() = 0;
    private:

    };
}