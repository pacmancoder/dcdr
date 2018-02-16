#include "MainFormWidgets.h"

#include <nana/paint/pixel_buffer.hpp>

using namespace Dcdr::Gui;

void MainFormWidgets::Initialize(nana::form& mainForm)
{

    // Main layout
    layout_.bind(mainForm);
    layout_.div(
            "margin=10 <vertical margin=[0, 5, 0, 0] <preview><weight=200 log>>" // left panel
                    "<vertical margin=[0, 5, 0, 0] weight=250<jobList><jobInfo><jobControls>>" // middle panel
                    "<vertical weight=250<nodeList><nodeInfo><nodeControls>>" // right panel
    );

    // root panels
    previewGroup_.create(mainForm);
    previewGroup_.caption("Job Preview");
    layout_["preview"] << previewGroup_;

    logGroup_.create(mainForm);
    logGroup_.caption("Dcdr Server Log");
    layout_["log"] << logGroup_;

    jobListGroup_.create(mainForm);
    jobListGroup_.caption("Job List");
    layout_["jobList"] << jobListGroup_;

    jobInfoGroup_.create(mainForm);
    jobInfoGroup_.caption("Current Job Info");
    layout_["jobInfo"] << jobInfoGroup_;

    jobControlsGroup_.create(mainForm);
    jobControlsGroup_.caption("Current Job Control");
    layout_["jobControls"] << jobControlsGroup_;

    nodeListGroup_.create(mainForm);
    nodeListGroup_.caption("Node List");
    layout_["nodeList"] << nodeListGroup_;

    nodeInfoGroup_.create(mainForm);
    nodeInfoGroup_.caption("Node Info");
    layout_["nodeInfo"] << nodeInfoGroup_;

    nodeControlsGroup_.create(mainForm);
    nodeControlsGroup_.caption("Current Node Control");
    layout_["nodeControls"] << nodeControlsGroup_;

    // Preview
    previewLayout_.bind(previewGroup_);
    previewLayout_.div("margin=20 previewPanel");

    previewPanel_.create(previewGroup_);
    previewLayout_["previewPanel"] << previewPanel_;

    // Log
    logLayout_.bind(logGroup_);
    logLayout_.div("margin=20 logBox");
    logTextBox_.create(logGroup_);
    logTextBox_.editable(false);
    logLayout_["logBox"] << logTextBox_;

    // job list
    jobListLayout_.bind(jobListGroup_);
    jobListLayout_.div("margin=20 jobListBox");
    jobListBox_.create(jobListGroup_);
    jobListBox_.append_header("State", 50);
    jobListBox_.append_header("Name", 146);
    jobListLayout_["jobListBox"] << jobListBox_;

    // job Info
    jobInfoLayout_.bind(jobInfoGroup_);
    jobInfoLayout_.div("margin=20 jobInfoListBox");
    jobInfoListBox_.create(jobInfoGroup_);
    jobInfoListBox_.append_header("Property", 98);
    jobInfoListBox_.append_header("Value", 98);
    jobInfoLayout_["jobInfoListBox"] << jobInfoListBox_;

    // job controls
    jobControlsLayout_.bind(jobControlsGroup_);
    jobControlsLayout_.div(
            "vertical margin=20"
                    "<max=30 <margin=3 stopButton><margin=3 resumeButton><margin=3 removeButton>>"
                    "<>"
                    "<max=30 <sceneLabel><sceneScaleLabel>>"
                    "<max=30 <margin=3 sceneComboBox><margin=3 sceneScaleSpinBox>>"
                    "<max=30 <sceneResolutionLabel><sceneResolutionValueLabel>>"
                    "<addButton>"
    );

    stopJobButton_.create(jobControlsGroup_);
    stopJobButton_.caption("Stop");
    jobControlsLayout_["stopButton"] << stopJobButton_;
    resumeJobButton_.create(jobControlsGroup_);
    resumeJobButton_.caption("Resume");
    jobControlsLayout_["resumeButton"] << resumeJobButton_;
    removeJobButton_.create(jobControlsGroup_);
    removeJobButton_.caption("Remove");
    jobControlsLayout_["removeButton"] << removeJobButton_;
    sceneLabel_.create(jobControlsGroup_);
    sceneLabel_.caption("Scene:");
    jobControlsLayout_["sceneLabel"] << sceneLabel_;
    sceneScaleLabel_.create(jobControlsGroup_);
    sceneScaleLabel_.caption("Scale:");
    jobControlsLayout_["sceneScaleLabel"] << sceneScaleLabel_;
    sceneComboBox_.create(jobControlsGroup_);
    jobControlsLayout_["sceneComboBox"] << sceneComboBox_;
    sceneScaleSpinBox_.create(jobControlsGroup_);
    sceneScaleSpinBox_.range(0.25, 4.0, 0.25);
    sceneScaleSpinBox_.caption("1.000000");
    jobControlsLayout_["sceneScaleSpinBox"] << sceneScaleSpinBox_;
    sceneResolutionLabel_.create(jobControlsGroup_);
    sceneResolutionLabel_.caption("Resolution:");
    jobControlsLayout_["sceneResolutionLabel"] << sceneResolutionLabel_;
    sceneResolutionValueLabel_.create(jobControlsGroup_);
    sceneResolutionValueLabel_.caption("640x480");
    jobControlsLayout_["sceneResolutionValueLabel"] << sceneResolutionValueLabel_;
    addJobButton_.create(jobControlsGroup_);
    addJobButton_.caption("Add Job");
    jobControlsLayout_["addButton"] << addJobButton_;

    // node list

    nodeListLayout_.bind(nodeListGroup_);
    nodeListLayout_.div("margin=20 jobListBox");
    nodeListBox_.create(nodeListGroup_);
    nodeListBox_.append_header("State", 50);
    nodeListBox_.append_header("Name", 146);
    nodeListLayout_["jobListBox"] << nodeListBox_;


    // node info
    nodeInfoLayout_.bind(nodeInfoGroup_);
    nodeInfoLayout_.div("margin=20 nodeInfoListBox");
    nodeInfoListBox_.create(nodeInfoGroup_);
    nodeInfoListBox_.append_header("Property", 98);
    nodeInfoListBox_.append_header("Value", 98);
    nodeInfoLayout_["nodeInfoListBox"] << nodeInfoListBox_;

    // node controls
    nodeControlsLayout_.bind(nodeControlsGroup_);
    nodeControlsLayout_.div(
            "vertical margin=20"
                    "<max=30 <margin=3 nodeEnableButton><margin=3 nodeDisableButton>>"
                    "<>"
    );
    nodeEnableButton_.create(nodeControlsGroup_);
    nodeEnableButton_.caption("Enable");
    nodeControlsLayout_["nodeEnableButton"] << nodeEnableButton_;
    nodeDisableButton_.create(nodeControlsGroup_);
    nodeDisableButton_.caption("Disable");
    nodeControlsLayout_["nodeDisableButton"] << nodeDisableButton_;

    layout_.collocate();
}