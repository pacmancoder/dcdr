#include <iostream>
#include <dcdr/Exception.h>
#include <dcdr/logging/Logger.h>
#include <dcdr/logging/StdoutLogWriter.h>

#include <dcdr/server/core/CoreContext.h>
#include <dcdr/server/service-commander/CommanderService.h>

#include <dcdr/server/loaders/DummySceneLoader.h>

#include <dcdr/transport/TcpAsyncServerTransport.h>

#include <chrono>

using namespace Dcdr::Server;
using namespace Dcdr::Logging;
using namespace Dcdr::Interconnect;
using namespace Dcdr::Transport;

using namespace std::chrono_literals;

int main(/* int argc, char* argv[] */)
{
    using namespace std::chrono_literals;
    Logger::get_instance().add_log_writer(std::unique_ptr<ILogWriter>(new StdoutLogWriter()));

    try
    {
        auto coreContext_ = std::make_shared<CoreContext>();

        DummySceneLoader sceneLoader;
        sceneLoader.load_scenes(coreContext_->get_scenes());
        // test code
        coreContext_->get_jobs().add(Job{0, 640, 480, 16});
        // test code end

        auto commanderService = std::make_shared<CommanderService>(coreContext_);

        TcpAsyncServerTransport transport("1206", 10s);
        transport.register_request_processor(commanderService);
        transport.run();

        std::cin.get();

        transport.close();
    }
    catch (Dcdr::DcdrException& e)
    {
        log_error(e.to_string());
        return 1;
    }
    catch (std::exception& e)
    {
        log_error(e.what());
        return 1;
    }
    catch (...)
    {
        log_error("[Server] Unexpected error happened. Terminating...");
        return 1;
    }
}