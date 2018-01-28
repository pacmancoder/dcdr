#include <iostream>
#include <dcdr/Exception.h>
#include <dcdr/logging/Logger.h>
#include <dcdr/logging/StdoutLogWriter.h>
#include <dcdr/server/core/Core.h>
#include <dcdr/server/transport/mongoose-websocket/MongooseWebsocket.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelDeserializer.h>

using namespace Dcdr::Logging;
using namespace Dcdr::Server;
using namespace Dcdr::Interconnect;

int main(/* int argc, char* argv[] */)
{

    Logger::get_instance().add_log_writer(std::unique_ptr<ILogWriter>(new StdoutLogWriter()));

    try
    {
        auto core = std::make_shared<Core>();
        auto serializer = std::make_shared<FlatBuffersParcelSerializer>();
        auto deserializer = std::make_shared<FlatBuffersParcelDeserializer>();

        MongooseWebsocket mongooseWebsocket(core, serializer, deserializer);
        mongooseWebsocket.open();

        core->run();

        mongooseWebsocket.close();
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