#include <webserver/WebServer.h>
#include <iostream>
#include <dcdr/logging/Logger.h>
#include <dcdr/logging/StdoutLogWriter.h>

using namespace Dcdr::Server;
using namespace Dcdr::Logging;

int main(int argc, char* argv[])
{
    Logger::get_instance().add_log_writer(std::unique_ptr<ILogWriter>(new StdoutLogWriter()));

    log_error("Error");
    log_warning("Warning");
    log_info("Info");
    log_debug("Debug");

    WebServer web_server(8000, "");
    web_server.run();

    std::cin.get();

    web_server.stop();
}