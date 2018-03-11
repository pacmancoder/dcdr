#include "../include/dcdr/gui/MainForm.h"

#include <vector>
#include <mutex>

#include "../include/dcdr/gui/MainFormWidgets.h"
#include "../include/dcdr/gui/ICommander.h"

#include <nana/paint/pixel_buffer.hpp>
#include <nana/gui/msgbox.hpp>
#include <nana/threads/pool.hpp>
#include <iostream>

using namespace Dcdr;
using namespace Dcdr::Gui;


namespace
{
    const std::string DEFAULT_WINDOW_CAPTION("DCDR CommanderNode");
    const size_t DEFAULT_FORM_WIDTH(1024);
    const size_t DEFAULT_FORM_HEIGHT(600);

    struct SceneData
    {
        uint32_t id;
        uint16_t width;
        uint16_t height;
    };

    struct MainFormCommanderData
    {
        std::vector<uint32_t> nodeIds_;
        std::vector<uint32_t> jobIds_;
        std::vector<SceneData> scenes_;

        MainFormCommanderData() = default;
        MainFormCommanderData(const MainFormCommanderData&) = delete;
        MainFormCommanderData(MainFormCommanderData&&) = delete;
        MainFormCommanderData& operator=(const MainFormCommanderData&) = delete;
    };

    std::string stringify(Interconnect::Commander::NodeState state)
    {
        std::string stateStr = "Unknown";
        switch (state)
        {
            case Interconnect::Commander::NodeState::Active:
            {
                stateStr = "Active";
                break;
            }
            case Interconnect::Commander::NodeState::Disabled:
            {
                stateStr = "Disabled";
                break;
            }
            case Interconnect::Commander::NodeState::Malfunctioned:
            {
                stateStr = "Malfunction";
                break;
            }
            case Interconnect::Commander::NodeState::Offline:
            {
                stateStr = "Offline";
                break;
            }
        }
        return stateStr;
    }

    std::string stringify(Interconnect::Commander::JobState state)
    {
        std::string stateStr = "Unknown";
        switch (state)
        {
            case Interconnect::Commander::JobState::InProgress:
            {
                stateStr = "In progress";
                break;
            }
            case Interconnect::Commander::JobState::Stopped:
            {
                stateStr = "Stopped";
                break;
            }
            case Interconnect::Commander::JobState::Removed:
            {
                stateStr = "Removed";
                break;
            }
        }
        return stateStr;
    }
}
struct MainForm::Impl
{
public:
    Impl() = default;

    void update_new_scene_params();

public:
    MainFormWidgets widgets_;

    MainFormCommanderData commanderData_;
    std::recursive_mutex commanderDataMutex_;

    std::weak_ptr<ICommander> commander_;
    bool closePending_ = false;

    struct
    {
        uint16_t width = 0;
        uint16_t height = 0;
    } new_scene_resolution;

    float new_scene_scale = 1.0f;
    uint32_t new_scene_id = std::numeric_limits<uint32_t>::max();
};

void MainForm::Impl::update_new_scene_params()
{
    std::lock_guard<std::recursive_mutex> guard(commanderDataMutex_);

    if (widgets_.sceneComboBox_.option() >= commanderData_.scenes_.size())
    {
        return;
    }

    auto scene = commanderData_.scenes_[widgets_.sceneComboBox_.option()];
    new_scene_id = scene.id;

    auto scale = widgets_.sceneScaleSpinBox_.to_double();

    new_scene_resolution.width = static_cast<uint16_t>(scale * scene.width);
    new_scene_resolution.height = static_cast<uint16_t>(scale * scene.height);

    new_scene_scale = static_cast<float>(scale);

    widgets_.sceneResolutionValueLabel_.caption(
            std::to_string(new_scene_resolution.width) + "x" + std::to_string(new_scene_resolution.height));
}

Dcdr::Gui::MainForm::MainForm() :
        form(nana::API::make_center(DEFAULT_FORM_WIDTH, DEFAULT_FORM_HEIGHT)),
        impl_(new Impl())
{
    caption(DEFAULT_WINDOW_CAPTION);

    events().unload([this](const nana::arg_unload& event)
    {
        if (auto commander = impl_->commander_.lock())
        {
            if (!impl_->closePending_)
            {
                commander->request_terminate();
                event.cancel = true;
            }
        }
        // if no commander attached - just close window.
    });

    impl_->widgets_.Initialize(*this);

    impl_->widgets_.sceneScaleSpinBox_.events().text_changed([this](const nana::arg_spinbox&)
    {
        impl_->update_new_scene_params();
    });

    impl_->widgets_.sceneComboBox_.events().text_changed([this](const nana::arg_combox&)
    {
        impl_->update_new_scene_params();
    });

    impl_->widgets_.addJobButton_.events().click([this](const nana::arg_click& event)
    {
       if (event.mouse_args->button == nana::mouse::left_button)
       {
           impl_->update_new_scene_params();
           if (auto commander = impl_->commander_.lock())
           {
               commander->add_job(
                       impl_->new_scene_id,
                       impl_->new_scene_scale);
           }
       }
    });

    impl_->widgets_.jobListBox_.events().selected([this](const nana::arg_listbox& event)
    {
       if (auto commander = impl_->commander_.lock())
       {
           commander->select_job(static_cast<uint32_t>(event.item.pos().item));
       }
    });
}

void MainForm::clear_nodes()
{
    std::lock_guard<std::recursive_mutex> guard(impl_->commanderDataMutex_);
    impl_->widgets_.nodeListBox_.clear();
    impl_->commanderData_.nodeIds_.clear();
}

void MainForm::add_node(uint32_t id, const std::string& name, Interconnect::Commander::NodeState state)
{
    std::lock_guard<std::recursive_mutex> guard(impl_->commanderDataMutex_);
    impl_->widgets_.nodeListBox_.at(0).append({stringify(state), name});
    impl_->commanderData_.nodeIds_.push_back(id);
}

void MainForm::clear_node_info()
{
    std::lock_guard<std::recursive_mutex> guard(impl_->commanderDataMutex_);
    impl_->widgets_.nodeInfoListBox_.clear();
}

void MainForm::add_node_info(const std::string& name, const std::string& value)
{
    std::lock_guard<std::recursive_mutex> guard(impl_->commanderDataMutex_);
    impl_->widgets_.nodeInfoListBox_.at(0).append({name, value});
}

void MainForm::clear_jobs()
{
    std::lock_guard<std::recursive_mutex> guard(impl_->commanderDataMutex_);
    impl_->widgets_.jobListBox_.clear();
    impl_->commanderData_.jobIds_.clear();
}

void MainForm::add_job(uint32_t id, const std::string& name, Interconnect::Commander::JobState state)
{
    std::lock_guard<std::recursive_mutex> guard(impl_->commanderDataMutex_);
    impl_->widgets_.jobListBox_.at(0).append({stringify(state), name});
    impl_->commanderData_.jobIds_.push_back(id);
}

void MainForm::clear_scenes()
{
    std::lock_guard<std::recursive_mutex> guard(impl_->commanderDataMutex_);
    impl_->widgets_.sceneComboBox_.clear();
    impl_->commanderData_.scenes_.clear();
}

void MainForm::add_scene(uint32_t id, const std::string& name, uint16_t width, uint16_t height)
{
    std::lock_guard<std::recursive_mutex> guard(impl_->commanderDataMutex_);
    impl_->widgets_.sceneComboBox_.push_back(name + " (" + std::to_string(width) + "x" + std::to_string(height) + ")");
    if (impl_->commanderData_.scenes_.empty())
    {
        impl_->widgets_.sceneComboBox_.option(0);
    }
    impl_->commanderData_.scenes_.push_back({id, width, height});
}

void MainForm::display_preview(uint16_t width, uint16_t height, const uint8_t* data)
{
    std::lock_guard<std::recursive_mutex> guard(impl_->commanderDataMutex_);
    const size_t BYTES_PER_PIXEL = 3;
    const size_t BITS_PER_PIXEL = BYTES_PER_PIXEL * 8;

    nana::drawing drawing(impl_->widgets_.previewPanel_);

    nana::paint::pixel_buffer pb(width, height);
    for (int row = 0; row < height; ++row)
    {
        pb.fill_row(static_cast<size_t>(row),
                    data + row * width * BYTES_PER_PIXEL,
                    static_cast<size_t>(width * BYTES_PER_PIXEL),
                    BITS_PER_PIXEL);
    }

    drawing.clear();
    drawing.draw([pb=std::move(pb), width, height](nana::paint::graphics& g)
    {
        pb.paste(g.handle(), nana::point((g.width() - width) / 2, (g.height() - height) / 2));
    });
    drawing.update();
}

void MainForm::write_log_message(const std::string& message)
{
    std::lock_guard<std::recursive_mutex> guard(impl_->commanderDataMutex_);
    impl_->widgets_.logTextBox_.append(message, false);
}

void MainForm::show_error(const std::string& message)
{
    nana::msgbox msgbox(*this, std::string("Error"), nana::msgbox::button_t::ok);
    msgbox << message;
    msgbox.icon(nana::msgbox::icon_error);
    msgbox.show();
}

void MainForm::terminate()
{
    impl_->closePending_ = true;
    close();
}

void MainForm::clear_job_info()
{
    std::lock_guard<std::recursive_mutex> guard(impl_->commanderDataMutex_);
    impl_->widgets_.jobInfoListBox_.clear();
}

void MainForm::add_job_info(const std::string& name, const std::string& value)
{
    std::lock_guard<std::recursive_mutex> guard(impl_->commanderDataMutex_);
    impl_->widgets_.jobInfoListBox_.at(0).append({name, value});
}

void MainForm::attach_commander(std::weak_ptr<ICommander> commander)
{
    impl_->commander_ = std::move(commander);
}

Dcdr::Gui::MainForm::~MainForm() = default;
