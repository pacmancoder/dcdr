
#include "MainForm.h"
#include <memory>
#include <thread>
#include <future>
#include <chrono>

using namespace Dcdr::Gui;

namespace
{
    void sleep(size_t ms)
    {
        std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(ms));
    }
}

int main()
{
    auto mainForm = std::make_shared<std::unique_ptr<Dcdr::Gui::MainForm>>(nullptr);

    auto guiThread = std::thread([mainForm]() mutable
    {
        mainForm->reset(new Dcdr::Gui::MainForm());
        (*mainForm)->show();
        nana::exec();
    });

    auto commanderThread = std::thread([mainForm]()
    {
        sleep(1000);
        (*mainForm)->add_node(1, "Test 1", Dcdr::Interconnect::Commander::NodeState::Active); sleep(500);
        (*mainForm)->add_node(2, "WOWWWW", Dcdr::Interconnect::Commander::NodeState::Offline); sleep(500);
        (*mainForm)->add_node(3, "Куку!", Dcdr::Interconnect::Commander::NodeState::Offline); sleep(500);
        (*mainForm)->add_node(4, "Чё как?", Dcdr::Interconnect::Commander::NodeState::Offline); sleep(500);
        sleep(3000);
        (*mainForm)->clear_nodes();
        sleep(5000);
        (*mainForm)->terminate();
    });

    guiThread.join();
    commanderThread.join();
    return 0;
}