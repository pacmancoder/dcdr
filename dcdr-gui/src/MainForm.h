#pragma once

#include <nana/gui/wvl.hpp>

#include <memory>

#include "IMainFormView.h"
#include "ICommander.h"

namespace Dcdr::Gui
{
    class MainForm : public nana::form
    {
    public:
        MainForm();

        ~ MainForm();
    private:
        void InitializeWidgets();

    private:
        struct Impl;

        std::unique_ptr<Impl> impl_;
    };
}