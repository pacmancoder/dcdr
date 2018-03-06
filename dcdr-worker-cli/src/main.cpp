
#include <dcdr/worker/WorkerNode.h>
#include <dcdr/logging/Logger.h>
#include <dcdr/logging/StdoutLogWriter.h>

using namespace Dcdr::Logging;
using namespace Dcdr::Worker;

int main(int /*argc*/, char** /*argv*/) {

    Logger::get_instance().add_log_writer(std::make_unique<StdoutLogWriter>());

    WorkerNode node;

    node.run();

    return 0;
}