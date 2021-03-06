#include <iostream>
#include <dcdr/Exception.h>
#include <dcdr/logging/Logger.h>
#include <dcdr/logging/StdoutLogWriter.h>
#include <dcdr/utils/ArgsParser.h>

#include <dcdr/server/core/CoreContext.h>

#include <dcdr/server/service-commander/CommanderService.h>
#include <dcdr/server/service-worker/WorkerService.h>

#include <dcdr/server/loaders/FSSceneLoader.h>

#include <dcdr/transport/WebsocketAsyncServerTransport.h>

#include <chrono>

using namespace Dcdr::Utils;
using namespace Dcdr::Server;
using namespace Dcdr::Logging;
using namespace Dcdr::Interconnect;
using namespace Dcdr::Transport;

using namespace std::chrono_literals;

int main(int argc, char* argv[])
{
    ArgsParser args(argc, argv);

    using namespace std::chrono_literals;

    auto& logger = Logger::get_instance();
    logger.add_log_writer(std::unique_ptr<ILogWriter>(new StdoutLogWriter()));
    #ifndef NDEBUG
        logger.enable_debug();
    #endif

    try
    {
        auto coreContext_ = std::make_shared<CoreContext>();

        FSSceneLoader sceneLoader(args.get_argument("scene-cache"));
        sceneLoader.load(*coreContext_);

        auto commanderService = std::make_shared<CommanderService>(coreContext_);
        WebsocketAsyncServerTransport commanderTransport("61296", 10s);
        commanderTransport.register_request_processor(commanderService);
        commanderTransport.run();


        auto workerService = std::make_shared<WorkerService>(coreContext_);
        WebsocketAsyncServerTransport workerTransport("61297", 10s);
        workerTransport.register_request_processor(workerService);
        workerTransport.run();


        for(;;)
        {
            std::string value;

            std::cin >> value;
            if (value == "@exit")
            {
                break;
            }
        }

        workerTransport.close();
        commanderTransport.close();
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