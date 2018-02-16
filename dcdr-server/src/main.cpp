#include <iostream>
#include <dcdr/Exception.h>
#include <dcdr/logging/Logger.h>
#include <dcdr/logging/StdoutLogWriter.h>

#include <dcdr/messaging/flatbuffers/FlatBuffersParcelDeserializer.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>

#include <dcdr/messaging/IParcelDispatcher.h>
#include <dcdr/messaging/commander/ICommanderRequestDispatcher.h>
#include <dcdr/messaging/commander/CommanderRequestParcels.h>
#include <dcdr/messaging/commander/CommanderResponseParcels.h>

#include <dcdr/transport/TcpAsyncServerTransport.h>

#include <chrono>
#include <iostream>
#include <future>

using namespace Dcdr::Logging;
using namespace Dcdr::Interconnect;
using namespace Dcdr::Transport;

using namespace std::chrono_literals;

namespace
{

    class ParcelDispatcher : public IParcelDispatcher, public ICommanderRequestDispatcher
    {
    public:
        IParcel::ParcelPtr dispatch(const ACommanderRequestParcel& parcel) override
        {
            return parcel.dispatch(static_cast<ICommanderRequestDispatcher&>(*this));
        }

        IParcel::ParcelPtr dispatch(const CommanderGetSceneListRequest&) override
        {
            std::vector<Commander::Scene> scenes;
            scenes.push_back(Commander::Scene {0, "Test1", 640, 480});
            scenes.push_back(Commander::Scene {1, "Cornell", 1980, 1080});

            return std::make_unique<CommanderGetSceneListReponseParcel>(std::move(scenes));
        }

    };

    class RequestProcessor : public IAsyncConnectionProcessor
    {
    public:
        ResponseHandle get_response(size_t /*id*/, const Request& request) override
        {
            std::promise<std::vector<uint8_t>> promise;

            FlatBuffersParcelDeserializer deserializer;
            FlatBuffersParcelSerializer serializer;

            auto parcel = deserializer.deserialize(request);
            auto response = parcel->dispatch(dispatcher_);
            auto serialized = response->serialize(serializer);

            promise.set_value(serialized);
            return promise.get_future();
        }

        void open_connection(size_t /*id*/) override {}

        void close_connection(size_t /*id*/) override {}

    private:
        ParcelDispatcher dispatcher_;
    };
}

int main(/* int argc, char* argv[] */)
{

    Logger::get_instance().add_log_writer(std::unique_ptr<ILogWriter>(new StdoutLogWriter()));

    try
    {
        TcpAsyncServerTransport transport("1206", 10s);
        transport.register_request_processor(std::make_shared<RequestProcessor>());
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