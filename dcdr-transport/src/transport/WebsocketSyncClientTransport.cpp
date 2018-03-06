#include <dcdr/transport/WebsocketSyncClientTransport.h>
#include <dcdr/transport/TransportExceptions.h>
#include <dcdr/utils/Timer.h>
#include <dcdr/logging/Logger.h>

#include <mongoose.h>

#include <iostream>

#include "private/MongooseUtils.h"

using namespace Dcdr::Logging;
using namespace Dcdr::Transport;

namespace
{
    const char* LOG_PREFIX = "[Transport][TcpSyncClient] ";
    const int MONGOOSE_POOL_SUBINTERVAL = 50; // in milliseconds
}

struct WebsocketSyncClientTransport::Impl
{
    mg_mgr mgr;
    mg_connection* connection;

    bool connectionEstablished;
    bool sendDone;
    bool receiveDone;

    std::vector<uint8_t> receivedData;

    std::chrono::milliseconds networkTimeout;

    explicit Impl(std::chrono::milliseconds networkTimeout_) :
            mgr(),
            connection(nullptr),
            connectionEstablished(false),
            sendDone(false),
            receiveDone(false),
            networkTimeout(networkTimeout_) {}
};

namespace
{
    void client_handler(struct mg_connection *nc, int event, void* eventData)
    {
        auto* impl_ = reinterpret_cast<WebsocketSyncClientTransport::Impl*>(nc->mgr->user_data);

        switch (event)
        {
            case MG_EV_WEBSOCKET_HANDSHAKE_DONE:
            {
                log_debug(LOG_PREFIX, "Connection with ", Mongoose::socket_to_string(nc->sa), " established");

                impl_->connection = nc;
                impl_->connectionEstablished = true;
                break;
            }
            case MG_EV_CLOSE:
            {
                log_debug(LOG_PREFIX, "Connection with ", Mongoose::socket_to_string(nc->sa), " closed");

                impl_->connection = nullptr;
                impl_->connectionEstablished = false;
                break;
            }
            case MG_EV_SEND:
            {
                log_trace(LOG_PREFIX, "Sent data to ", Mongoose::socket_to_string(nc->sa));

                impl_->sendDone = true;
                break;
            }
            case MG_EV_WEBSOCKET_FRAME:
            {
                const auto* receivedMessage = reinterpret_cast<const websocket_message*>(eventData);
                if ((receivedMessage->flags & 0x0F) != WEBSOCKET_OP_BINARY)
                {
                    break;
                }

                std::vector<uint8_t> received(receivedMessage->data, receivedMessage->data + receivedMessage->size);

                log_trace(LOG_PREFIX, "Received data from ", Mongoose::socket_to_string(nc->sa), " with size ", receivedMessage->size);

                impl_->receivedData = std::move(received);
                impl_->receiveDone = true;
                break;
            }
            default:
                break;
        }
    }
}

WebsocketSyncClientTransport::WebsocketSyncClientTransport(const std::string& address, std::chrono::milliseconds networkTimeout) :
    impl_(new Impl(networkTimeout))
{
    mg_mgr_init(&impl_->mgr, impl_.get());
    if (!mg_connect_ws(&impl_->mgr, client_handler, (std::string("ws://").append(address)).c_str(), nullptr, nullptr))
    {
        throw ConnectionException(std::string("Can't connect to host ").append(address));
    }

    Utils::Timer connectionTimeoutTimer(impl_->networkTimeout);
    while(!(impl_->connectionEstablished))
    {
        mg_mgr_poll(&impl_->mgr, MONGOOSE_POOL_SUBINTERVAL);

        if (connectionTimeoutTimer.elapsed())
        {
            throw ConnectionException(std::string("Can't connect to host ").append(address));
        }
    }
}

WebsocketSyncClientTransport::~WebsocketSyncClientTransport()
{
    mg_mgr_free(&impl_->mgr);
}

void WebsocketSyncClientTransport::send(const ISyncClientTransport::Request& data)
{
    log_trace(LOG_PREFIX, "Sending ", data.size(), " bytes over network");

    mg_send_websocket_frame(impl_->connection, WEBSOCKET_OP_BINARY, data.data(), data.size());

    Utils::Timer sendTimeoutTimer(impl_->networkTimeout);
    while (!impl_->sendDone)
    {
        mg_mgr_poll(&impl_->mgr, MONGOOSE_POOL_SUBINTERVAL);

        if (sendTimeoutTimer.elapsed())
        {
            throw ConnectionException(std::string("Can't send data over network, timeout exceeded"));
        }
    }

    impl_->sendDone = false;
}

ISyncClientTransport::ResponsePtr WebsocketSyncClientTransport::receive()
{
    Utils::Timer receiveTimeoutTimer(impl_->networkTimeout);
    while (!impl_->receiveDone)
    {
        mg_mgr_poll(&impl_->mgr, MONGOOSE_POOL_SUBINTERVAL);

        if (receiveTimeoutTimer.elapsed())
        {
            throw ConnectionException(std::string("Can't receive data from network, timeout exceeded"));
        }
    }

    impl_->receiveDone = false;
    return std::make_unique<ISyncClientTransport::Response>(std::move(impl_->receivedData));
}

void WebsocketSyncClientTransport::send_request(const ISyncClientTransport::Request& request)
{
    send(request);
}

ISyncClientTransport::ResponsePtr WebsocketSyncClientTransport::get_response(const Request& request)
{
    send(request);
    return receive();
}
