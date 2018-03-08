#include "../include/dcdr/gui/MainForm.h"
#include "dcdr/gui/CommanderNode.h"
#include <dcdr/logging/Logger.h>
#include <dcdr/logging/StdoutLogWriter.h>
#include <dcdr/Exception.h>

#include <memory>
#include <thread>
#include <future>
#include <chrono>

using namespace Dcdr::Gui;
using namespace Dcdr::Logging;

int main()
{
    Logger::get_instance().add_log_writer(std::make_unique<StdoutLogWriter>());

    // gui will start on promary application thread
    auto mainForm = std::make_shared<Dcdr::Gui::MainForm>();

    // while commander communication logic should  be started on another thread
    auto commanderThread = std::thread([mainForm]()
    {
        try
        {
            auto commander = std::make_shared<CommanderNode>(mainForm);
            mainForm->attach_commander(commander);
            commander->run();
        }
        catch (const Dcdr::DcdrException& e)
        {
            log_error(e.to_string());
        }
        catch (const std::exception& e)
        {
            log_error(std::string("[GUI][CommanderNode] Unknown error: ").append(e.what()));
        }

    });

    mainForm->show();
    nana::exec();
    commanderThread.join();
    
    return 0;
}