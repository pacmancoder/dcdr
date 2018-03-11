
#include <dcdr/worker/WorkerNode.h>
#include <dcdr/logging/Logger.h>
#include <dcdr/logging/StdoutLogWriter.h>

using namespace Dcdr::Logging;
using namespace Dcdr::Worker;

int main(int /*argc*/, char** /*argv*/) {

    auto& logger = Logger::get_instance();
    logger.add_log_writer(std::unique_ptr<ILogWriter>(new StdoutLogWriter()));
    #ifndef NDEBUG
        logger.enable_debug();
    #endif

    WorkerNode node;

    node.run();

    return 0;
}