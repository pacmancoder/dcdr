#include <dcdr/server/transport/mongoose-websocket/MongooseWebsocket.h>

#include <mongoose.h>

#include <dcdr/logging/Logger.h>
#include <dcdr/messaging/AParcelSerializer.h>
#include <dcdr/messaging/AParcelDeserializer.h>
#include <dcdr/server/core/Core.h>
#include <dcdr/server/transport/mongoose-common/MongooseExceptions.h>

using namespace Dcdr::Server;
using namespace Dcdr::Logging;

namespace Dcdr::Server
{
    struct MongooseWebsocket::MongooseWebsocketImpl
    {
    public:
        void process_frame(mg_connection* connection, websocket_message *message);

        void open();
        void close();

    public:
        mg_mgr mongoose_manager_;
        std::thread workerThread_;
        std::atomic<bool> serverInterrupted_;

        MongooseWebsocket::ParcelSerizlizerPtr serizlizer_;
        MongooseWebsocket::ParcelDeserializerPtr deserizlizer_;
        MongooseWebsocket::CorePtr core_;
    };
}

namespace
{

    const int DEFAULT_WEBSOCKET_PORT = 8080;
    const int DEFAULT_POLL_TIME = 25;

    enum class WebsocketEvent
    {
        Unknown,
        Frame,
        Control,
        NewConnection,
        ConnectionClosed,
    };


    std::string mongoose_get_connection_address(mg_connection* connection)
    {
        const size_t MAX_ADDRESS_STRING_SIZE(32);
        char buffer[MAX_ADDRESS_STRING_SIZE]{};
        mg_sock_addr_to_str(
                &connection->sa,
                buffer,
                MAX_ADDRESS_STRING_SIZE,
                MG_SOCK_STRINGIFY_IP | MG_SOCK_STRINGIFY_PORT);
        return std::string(buffer);
    }

    WebsocketEvent websocket_event_from_mongoose_event(int event)
    {
        switch (event)
        {
            case MG_EV_WEBSOCKET_FRAME: return WebsocketEvent::Frame;
            case MG_EV_WEBSOCKET_CONTROL_FRAME: return WebsocketEvent::Control;
            case MG_EV_WEBSOCKET_HANDSHAKE_DONE: return WebsocketEvent::NewConnection;
            case MG_EV_CLOSE: return WebsocketEvent::ConnectionClosed;
            default:return WebsocketEvent::Unknown;
        }
    }

    void mongoose_event_handler(mg_connection* connection, int event, void* data)
    {
        switch(websocket_event_from_mongoose_event(event))
        {
            case WebsocketEvent::Frame:
            {
                log_info(std::string("[Server][MongooseWebsocket] Processing frame form ")
                                 .append(mongoose_get_connection_address(connection)));

                reinterpret_cast<MongooseWebsocket::MongooseWebsocketImpl*>(connection->mgr->user_data)->process_frame(
                        connection, reinterpret_cast<websocket_message*>(data));

                log_info(std::string("[Server][MongooseWebsocket] Frame form ")
                                 .append(mongoose_get_connection_address(connection))
                                 .append(" was processed"));
                break;
            }
            case WebsocketEvent::Control:
            {
                auto controlMessage = reinterpret_cast<websocket_message*>(data);

                if (controlMessage->flags == WEBSOCKET_OP_PING)
                {
                    log_info(std::string("[Server][MongooseWebsocket] Ping  from ")
                                     .append(mongoose_get_connection_address(connection))
                                     .append(" received"));

                    mg_send_websocket_frame(connection, WEBSOCKET_OP_PONG, nullptr, 0);
                    log_info(std::string("[Server][MongooseWebsocket] Pong  to ")
                                     .append(mongoose_get_connection_address(connection))
                                     .append(" was sent"));
                }
                break;
            }
            case WebsocketEvent::NewConnection:
            {
                log_info(std::string("[Server][MongooseWebsocket] New connection from " )
                                 .append(mongoose_get_connection_address(connection)));
                break;
            }
            case WebsocketEvent::ConnectionClosed:
            {
                log_info(std::string("[Server][MongooseWebsocket] Connection from " )
                                 .append(mongoose_get_connection_address(connection))
                                 .append(" closed"));
            }
            default:
            {
                return;
            }
        }
    }

    std::unique_ptr<MongooseWebsocket::MongooseWebsocketImpl> construct_mongoose_server(
            const MongooseWebsocket::CorePtr& core,
            const MongooseWebsocket::ParcelSerizlizerPtr& serizlizer,
            const MongooseWebsocket::ParcelDeserializerPtr& deserizlizer)
    {
        std::unique_ptr<MongooseWebsocket::MongooseWebsocketImpl> server(
                new MongooseWebsocket::MongooseWebsocketImpl {});

        server->workerThread_ = std::thread();
        server->serverInterrupted_ = false;

        server->core_ = core;
        server->serizlizer_ = serizlizer;
        server->deserizlizer_ = deserizlizer;

        mg_mgr_init(&server->mongoose_manager_, server.get());

        auto connection = mg_bind(
                &server->mongoose_manager_,
                std::to_string(DEFAULT_WEBSOCKET_PORT).c_str(),
                mongoose_event_handler);

        if (connection == nullptr)
        {
            throw MongooseException("Can't bind port " + std::to_string(DEFAULT_WEBSOCKET_PORT));
        }

        mg_set_protocol_http_websocket(connection);

        return std::move(server);
    }
}

void MongooseWebsocket::MongooseWebsocketImpl::process_frame(mg_connection* connection, websocket_message* message)
{
    if (!(message->flags & WEBSOCKET_OP_BINARY))
    {
        log_warning("[Server][Mongoose] Wrong WebSocket frame type");
        return;
    }

    auto requestParcel = deserizlizer_->deserialize(std::vector<uint8_t>(
            static_cast<const uint8_t*>(message->data),
            static_cast<const uint8_t*>(message->data + message->size)));

    if (requestParcel == nullptr)
    {
        log_error("[Server][Mongoose] Can't deserialize - parcel not supported");
        return;
    }

    auto responseParcelFuture = requestParcel->dispatch(*core_);

    if (responseParcelFuture.valid())
    {
        auto responseParcel = responseParcelFuture.get();
        auto serializedResponse = responseParcel->serialize(*serizlizer_);

        if (!serializedResponse.empty())
        {
            mg_send_websocket_frame(
                    connection,
                    WEBSOCKET_OP_BINARY,
                    serializedResponse.data(),
                    serializedResponse.size());
        }
    }
}

void MongooseWebsocket::MongooseWebsocketImpl::open()
{
    workerThread_ = std::thread([&]() {
       for(;!serverInterrupted_;)
       {
           mg_mgr_poll(&mongoose_manager_, DEFAULT_POLL_TIME);
       }
    });
}

void MongooseWebsocket::MongooseWebsocketImpl::close()
{
    serverInterrupted_ = true;
    workerThread_.join();
}

MongooseWebsocket::MongooseWebsocket(const MongooseWebsocket::CorePtr& core,
                                     const MongooseWebsocket::ParcelSerizlizerPtr& serizlizer,
                                     const MongooseWebsocket::ParcelDeserializerPtr& deserizlizer) :
    impl_(construct_mongoose_server(core, serizlizer, deserizlizer)) {}

void MongooseWebsocket::open()
{
    impl_->open();
}

void MongooseWebsocket::close()
{
    impl_->close();
}

MongooseWebsocket::~MongooseWebsocket() = default;
