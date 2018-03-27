
#include <dcdr/Exception.h>
#include <dcdr/worker/WorkerNode.h>
#include <dcdr/logging/Logger.h>
#include <dcdr/logging/StdoutLogWriter.h>
#include <dcdr/utils/ArgsParser.h>

#include <iostream>
#include <dcdr/worker/SceneStorage.h>

using namespace Dcdr::Logging;
using namespace Dcdr::Worker;
using namespace Dcdr::Utils;

int main(int argc, char* argv[]) {

    ArgsParser args(argc, argv);

    auto& logger = Logger::get_instance();
    logger.add_log_writer(std::unique_ptr<ILogWriter>(new StdoutLogWriter()));
    #ifndef NDEBUG
        logger.enable_debug();
    #endif

    try
    {
        WorkerNode node(args);

        node.run();
    }
    catch (const Dcdr::DcdrException& e)
    {
        log_error("CRITICAL ERROR: ", e.to_string());
    }
    catch (const std::exception& e)
    {
        log_error("UNKNOWN CRITICAL ERROR:", e.what());
    }

    return 0;
}