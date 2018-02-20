#include <dcdr/transport/TcpSyncClientTransport.h>
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
    const int MONGOOSE_POOL_SUBINTERVAL = 50; // in milliseconds

    std::string with_log_prefix(const std::string& message)
    {
        return std::string("[Transport][TcpSyncClient] ").append(message);
    };
}

struct TcpSyncClientTransport::Impl
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
    void client_handler(struct mg_connection *nc, int event, void*)
    {
        auto* impl_ = reinterpret_cast<TcpSyncClientTransport::Impl*>(nc->mgr->user_data);

        switch (event)
        {
            case MG_EV_CONNECT:
            {
                impl_->connection = nc;
                impl_->connectionEstablished = true;
                log_info(with_log_prefix("Connection with ")
                                  .append(Mongoose::socket_to_string(nc->sa)).append(" established"));
                break;
            }
            case MG_EV_CLOSE:
            {
                log_info(with_log_prefix("Connection with ")
                                  .append(Mongoose::socket_to_string(nc->sa)).append(" closed"));
                impl_->connection = nullptr;
                impl_->connectionEstablished = false;
                break;
            }
            case MG_EV_SEND:
            {
                log_debug(with_log_prefix("Sent data to ")
                                  .append(Mongoose::socket_to_string(nc->sa)));
                impl_->sendDone = true;
                break;
            }
            case MG_EV_RECV:
            {
                std::vector<uint8_t> received(nc->recv_mbuf.buf, nc->recv_mbuf.buf + nc->recv_mbuf.len);
                mbuf_remove(&nc->recv_mbuf, nc->recv_mbuf.len);

                log_debug(with_log_prefix("Received data from ")
                                  .append(Mongoose::socket_to_string(nc->sa)));
                impl_->receivedData = std::move(received);
                impl_->receiveDone = true;
                break;
            }
            default: break;
        }
    }
}

TcpSyncClientTransport::TcpSyncClientTransport(const std::string& address, std::chrono::milliseconds networkTimeout) :
    impl_(new Impl(networkTimeout))
{
    mg_mgr_init(&impl_->mgr, impl_.get());
    if (!mg_connect(&impl_->mgr, address.c_str(), client_handler))
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

TcpSyncClientTransport::~TcpSyncClientTransport()
{
    mg_mgr_free(&impl_->mgr);
}

void TcpSyncClientTransport::send(const ISyncClientTransport::Request& data)
{
    mg_send(impl_->connection, data.data(), static_cast<int>(data.size()));

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

ISyncClientTransport::ResponsePtr TcpSyncClientTransport::receive()
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

ISyncClientTransport::ResponsePtr TcpSyncClientTransport::get_response(const Request& request)
{
    send(request);
    return receive();
}
