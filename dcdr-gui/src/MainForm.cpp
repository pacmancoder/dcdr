#include "MainForm.h"

#include <nana/gui/widgets/group.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/paint/pixel_buffer.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/spinbox.hpp>

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

}

namespace
{
    struct MainFormWidgets
    {

    };
}

struct MainForm::Impl
{
    nana::place layout_;

    // root panels
    nana::group previewGroup_;
    nana::group logGroup_;
    nana::group jobListGroup_;
    nana::group jobInfoGroup_;
    nana::group jobControlsGroup_;
    nana::group nodeListGroup_;
    nana::group nodeInfoGroup_;
    nana::group nodeControlsGroup_;

    // preview
    nana::place previewLayout_;
    nana::panel<true> previewPanel_;
    // log
    nana::place logLayout_;
    nana::textbox logTextBox_;

    // job list
    nana::place jobListLayout_;
    nana::listbox jobListBox_;
    // job Info
    nana::place jobInfoLayout_;
    nana::listbox jobInfoListBox_;
    // job controls
    nana::place jobControlsLayout_;
    nana::button stopJobButton_;
    nana::button resumeJobButton_;
    nana::button removeJobButton_;
    nana::label sceneLabel_;
    nana::label sceneScaleLabel_;
    nana::combox sceneComboBox_;
    nana::spinbox sceneScaleSpinBox_;
    nana::label sceneResolutionLabel_;
    nana::label sceneResolutionValueLabel_;
    nana::button addJobButton_;

    // node list
    nana::place nodeListLayout_;
    nana::listbox nodeListBox_;

    // node info
    nana::place nodeInfoLayout_;
    nana::listbox nodeInfoListBox_;

    // node controls
    nana::place nodeControlsLayout_;
    nana::button nodeEnableButton_;
    nana::button nodeDisableButton_;

    Impl() = default;
};

Dcdr::Gui::MainForm::MainForm() :
        form(get_default_form_rect()),
        impl_(new Impl())
{
    caption("DCDR Commander");
    InitializeWidgets();
}

void Dcdr::Gui::MainForm::InitializeWidgets()
{

    // Main layout
    impl_->layout_.bind(*this);
    impl_->layout_.div(
            "margin=10 <vertical margin=[0, 5, 0, 0] <preview><weight=200 log>>" // left panel
            "<vertical margin=[0, 5, 0, 0] weight=250<jobList><jobInfo><jobControls>>" // middle panel
            "<vertical weight=250<nodeList><nodeInfo><nodeControls>>" // right panel
    );

    // root panels
    impl_->previewGroup_.create(*this);
    impl_->previewGroup_.caption("Job Preview");
    impl_->layout_["preview"] << impl_->previewGroup_;

    impl_->logGroup_.create(*this);
    impl_->logGroup_.caption("Dcdr Server Log");
    impl_->layout_["log"] << impl_->logGroup_;

    impl_->jobListGroup_.create(*this);
    impl_->jobListGroup_.caption("Job List");
    impl_->layout_["jobList"] << impl_->jobListGroup_;

    impl_->jobInfoGroup_.create(*this);
    impl_->jobInfoGroup_.caption("Current Job Info");
    impl_->layout_["jobInfo"] << impl_->jobInfoGroup_;

    impl_->jobControlsGroup_.create(*this);
    impl_->jobControlsGroup_.caption("Current Job Control");
    impl_->layout_["jobControls"] << impl_->jobControlsGroup_;

    impl_->nodeListGroup_.create(*this);
    impl_->nodeListGroup_.caption("Node List");
    impl_->layout_["nodeList"] << impl_->nodeListGroup_;

    impl_->nodeInfoGroup_.create(*this);
    impl_->nodeInfoGroup_.caption("Node Info");
    impl_->layout_["nodeInfo"] << impl_->nodeInfoGroup_;

    impl_->nodeControlsGroup_.create(*this);
    impl_->nodeControlsGroup_.caption("Current Node Control");
    impl_->layout_["nodeControls"] << impl_->nodeControlsGroup_;

    // Preview
    impl_->previewLayout_.bind(impl_->previewGroup_);
    impl_->previewLayout_.div("margin=20 previewPanel");

    impl_->previewPanel_.create(impl_->previewGroup_);
    impl_->previewLayout_["previewPanel"] << impl_->previewPanel_;

    nana::drawing drawing(impl_->previewPanel_);
    drawing.draw([](nana::paint::graphics& g)
                 {
                     for (size_t x = 0, y = 0; y < g.height(); y += (x++ + 1) / g.width(), x = x % g.width())
                     {
                         g.set_pixel(x, y, nana::color(
                                 static_cast<uint8_t>(static_cast<double>(x) / g.width() * 255),
                                 static_cast<uint8_t>(static_cast<double>(g.width() - x) / g.width() * 255),
                                 static_cast<uint8_t>(static_cast<double>(y) / g.width() * 255)
                         ));
                     }
                 });

    // Log
    impl_->logLayout_.bind(impl_->logGroup_);
    impl_->logLayout_.div("margin=20 logBox");
    impl_->logTextBox_.create(impl_->logGroup_);
    impl_->logTextBox_.editable(false);
    impl_->logLayout_["logBox"] << impl_->logTextBox_;

    // job list
    impl_->jobListLayout_.bind(impl_->jobListGroup_);
    impl_->jobListLayout_.div("margin=20 jobListBox");
    impl_->jobListBox_.create(impl_->jobListGroup_);
    impl_->jobListBox_.append_header("State", 50);
    impl_->jobListBox_.append_header("Name", 146);
    impl_->jobListLayout_["jobListBox"] << impl_->jobListBox_;

    // job Info
    impl_->jobInfoLayout_.bind(impl_->jobInfoGroup_);
    impl_->jobInfoLayout_.div("margin=20 jobInfoListBox");
    impl_->jobInfoListBox_.create(impl_->jobInfoGroup_);
    impl_->jobInfoListBox_.append_header("Property", 98);
    impl_->jobInfoListBox_.append_header("Value", 98);
    impl_->jobInfoLayout_["jobInfoListBox"] << impl_->jobInfoListBox_;

    // job controls
    impl_->jobControlsLayout_.bind(impl_->jobControlsGroup_);
    impl_->jobControlsLayout_.div(
            "vertical margin=20"
            "<max=30 <margin=3 stopButton><margin=3 resumeButton><margin=3 removeButton>>"
            "<>"
            "<max=30 <sceneLabel><sceneScaleLabel>>"
            "<max=30 <margin=3 sceneComboBox><margin=3 sceneScaleSpinBox>>"
            "<max=30 <sceneResolutionLabel><sceneResolutionValueLabel>>"
            "<addButton>"
    );

    impl_->stopJobButton_.create(impl_->jobControlsGroup_);
    impl_->stopJobButton_.caption("Stop");
    impl_->jobControlsLayout_["stopButton"] << impl_->stopJobButton_;
    impl_->resumeJobButton_.create(impl_->jobControlsGroup_);
    impl_->resumeJobButton_.caption("Resume");
    impl_->jobControlsLayout_["resumeButton"] << impl_->resumeJobButton_;
    impl_->removeJobButton_.create(impl_->jobControlsGroup_);
    impl_->removeJobButton_.caption("Remove");
    impl_->jobControlsLayout_["removeButton"] << impl_->removeJobButton_;
    impl_->sceneLabel_.create(impl_->jobControlsGroup_);
    impl_->sceneLabel_.caption("Scene:");
    impl_->jobControlsLayout_["sceneLabel"] << impl_->sceneLabel_;
    impl_->sceneScaleLabel_.create(impl_->jobControlsGroup_);
    impl_->sceneScaleLabel_.caption("Scale:");
    impl_->jobControlsLayout_["sceneScaleLabel"] << impl_->sceneScaleLabel_;
    impl_->sceneComboBox_.create(impl_->jobControlsGroup_);
    impl_->sceneComboBox_.push_back("test");
    impl_->jobControlsLayout_["sceneComboBox"] << impl_->sceneComboBox_;
    impl_->sceneScaleSpinBox_.create(impl_->jobControlsGroup_);
    impl_->sceneScaleSpinBox_.value("1.0");
    impl_->sceneScaleSpinBox_.range(0.25, 4.0, 0.25);
    impl_->jobControlsLayout_["sceneScaleSpinBox"] << impl_->sceneScaleSpinBox_;
    impl_->sceneResolutionLabel_.create(impl_->jobControlsGroup_);
    impl_->sceneResolutionLabel_.caption("Resolution:");
    impl_->jobControlsLayout_["sceneResolutionLabel"] << impl_->sceneResolutionLabel_;
    impl_->sceneResolutionValueLabel_.create(impl_->jobControlsGroup_);
    impl_->sceneResolutionValueLabel_.caption("640x480");
    impl_->jobControlsLayout_["sceneResolutionValueLabel"] << impl_->sceneResolutionValueLabel_;
    impl_->addJobButton_.create(impl_->jobControlsGroup_);
    impl_->addJobButton_.caption("Add Job");
    impl_->jobControlsLayout_["addButton"] << impl_->addJobButton_;

    // node list

    impl_->nodeListLayout_.bind(impl_->nodeListGroup_);
    impl_->nodeListLayout_.div("margin=20 jobListBox");
    impl_->nodeListBox_.create(impl_->nodeListGroup_);
    impl_->nodeListBox_.append_header("State", 50);
    impl_->nodeListBox_.append_header("Name", 146);
    impl_->nodeListLayout_["jobListBox"] << impl_->nodeListBox_;


    // node info
    impl_->nodeInfoLayout_.bind(impl_->nodeInfoGroup_);
    impl_->nodeInfoLayout_.div("margin=20 nodeInfoListBox");
    impl_->nodeInfoListBox_.create(impl_->nodeInfoGroup_);
    impl_->nodeInfoListBox_.append_header("Property", 98);
    impl_->nodeInfoListBox_.append_header("Value", 98);
    impl_->nodeInfoLayout_["nodeInfoListBox"] << impl_->nodeInfoListBox_;

    // node controls
    impl_->nodeControlsLayout_.bind(impl_->nodeControlsGroup_);
    impl_->nodeControlsLayout_.div(
            "vertical margin=20"
            "<max=30 <margin=3 nodeEnableButton><margin=3 nodeDisableButton>>"
            "<>"
    );
    impl_->nodeEnableButton_.create(impl_->nodeControlsGroup_);
    impl_->nodeEnableButton_.caption("Enable");
    impl_->nodeControlsLayout_["nodeEnableButton"] << impl_->nodeEnableButton_;
    impl_->nodeDisableButton_.create(impl_->nodeControlsGroup_);
    impl_->nodeDisableButton_.caption("Disable");
    impl_->nodeControlsLayout_["nodeDisableButton"] << impl_->nodeDisableButton_;

    impl_->layout_.collocate();
}

Dcdr::Gui::MainForm::~MainForm() = default;
