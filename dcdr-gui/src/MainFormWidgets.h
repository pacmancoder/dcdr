#pragma once

#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/group.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/spinbox.hpp>

namespace Dcdr::Gui
{
    struct MainFormWidgets
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

        MainFormWidgets() = default;

        void Initialize(nana::form& mainForm);
    };
}