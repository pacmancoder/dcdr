#pragma once

#include <nana/gui/wvl.hpp>

#include <memory>

#include "IMainFormView.h"

namespace Dcdr::Gui
{
    class ICommander;

    class MainForm : public nana::form, public IMainFormView
    {
    public:
        MainForm();

        void clear_nodes() override;
        void add_node(uint32_t id, const std::string& name, Interconnect::Commander::NodeState state) override;
        void clear_node_info() override;
        void add_node_info(const std::string& name, const std::string& value) override;
        void clear_jobs() override;
        void add_job(uint32_t id, const std::string& name, Interconnect::Commander::JobState state) override;
        void clear_job_info() override;
        void add_job_info(const std::string& name, const std::string& value) override;
        void clear_scenes() override;
        void add_scene(uint32_t id, const std::string& name, uint16_t width, uint16_t height) override;
        void display_preview(uint16_t width, uint16_t height, const uint8_t* data) override;
        void write_log_message(const std::string& name) override;
        void show_error(const std::string& name) override;
        void terminate() override;

        void attach_commander(std::weak_ptr<ICommander> commander);

        ~MainForm();

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}