#include "MainForm.h"

#include <map>
#include <mutex>

#include "MainFormWidgets.h"

using namespace Dcdr::Gui;

namespace
{
    const size_t DEFAULT_FORM_WIDTH = 1024;
    const size_t DEFAULT_FORM_HEIGHT = 600;

    // Construction of nana::rect wrapped into function because it's construcotr is not-nonexcept
    nana::rectangle get_default_form_rect()
    {
        return nana::rectangle(
            nana::screen::primary_monitor_size().width / 2 -
                    static_cast<nana::size::value_type>(DEFAULT_FORM_WIDTH) / 2,
            nana::screen::primary_monitor_size().height / 2 -
                    static_cast<nana::size::value_type>(DEFAULT_FORM_HEIGHT) / 2,
            DEFAULT_FORM_WIDTH,
            DEFAULT_FORM_HEIGHT) ;
    }

    struct MainFormCommanderData
    {
        std::map<int, uint32_t> nodeIds_;

        MainFormCommanderData() = default;
        MainFormCommanderData(const MainFormCommanderData&) = delete;
        MainFormCommanderData(MainFormCommanderData&&) = delete;
        MainFormCommanderData& operator=(const MainFormCommanderData&) = delete;
    };
}
struct MainForm::Impl
{
    MainFormWidgets widgets_;

    Impl() = default;

    MainFormCommanderData commanderData_;
    std::mutex commanderDataMutex_;
};

Dcdr::Gui::MainForm::MainForm() :
        form(get_default_form_rect()),
        impl_(new Impl())
{
    caption("DCDR Commander");
    impl_->widgets_.Initialize(*this);
}

void MainForm::clear_nodes()
{
    impl_->widgets_.nodeListBox_.clear();

    std::lock_guard<std::mutex> guard(impl_->commanderDataMutex_);
    impl_->commanderData_.nodeIds_.clear();
}

void MainForm::add_node(uint32_t id, const std::string& name, Dcdr::Interconnect::Commander::NodeState state)
{
    std::string stateStr = "Unknown";
    switch (state)
    {
        case Interconnect::Commander::NodeState::Active: stateStr = "Active"; break;
        case Interconnect::Commander::NodeState::Disabled: stateStr = "Disabled"; break;;
        case Interconnect::Commander::NodeState::Malfunctioned: stateStr = "Malfunction"; break;
        case Interconnect::Commander::NodeState::Offline:stateStr = "Offline"; break;
    }

    impl_->widgets_.nodeListBox_.at(0).append({stateStr, name});
    std::lock_guard<std::mutex> guard(impl_->commanderDataMutex_);
    impl_->commanderData_.nodeIds_[impl_->commanderData_.nodeIds_.size()] = id;
}

void MainForm::clear_node_info()
{

}

void MainForm::add_node_info(const std::string& , const std::string& )
{

}

void MainForm::clear_jobs()
{

}

void MainForm::add_job(uint32_t , const std::string& , Dcdr::Interconnect::Commander::JobState )
{

}

void MainForm::clear_scenes()
{

}

void MainForm::add_scene(uint32_t , const std::string& , int , int )
{

}

void MainForm::display_preview(uint16_t , uint16_t , const uint8_t* )
{

}

void MainForm::write_log_message(const std::string& )
{

}

void MainForm::show_error(const std::string& )
{

}

void MainForm::terminate()
{
    close();
}

Dcdr::Gui::MainForm::~MainForm() = default;
