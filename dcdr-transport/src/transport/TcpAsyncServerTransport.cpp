#include <dcdr/transport/TcpAsyncServerTransport.h>
#include <dcdr/utils/Timer.h>
#include <dcdr/logging/Logger.h>

#include <dcdr/transport/TransportExceptions.h>

#include <mongoose.h>
#include <thread>
#include <list>
#include <functional>

#include <iostream>


#include "private/MongooseUtils.h"

using namespace Dcdr::Transport;
using namespace Dcdr::Logging;
using namespace std::chrono_literals;

namespace
{
    const int MONGOOSE_POOL_INTERVAL = 50;

    std::string with_log_prefix(const std::string& message)
    {
        return std::string("[Transport][TcpAsyncServer] ").append(message);
    };

    struct ResponseInfo
    {
        IAsyncConnectionProcessor::ResponseHandle handle;
        mg_connection* connection;

        ResponseInfo(ResponseInfo&& rhs) :
            handle(std::move(rhs.handle)), connection(rhs.connection) {}

        ResponseInfo& operator=(ResponseInfo&& rhs)
        {
            handle = std::move(rhs.handle);
            connection = rhs.connection;
            return *this;
        }

        ResponseInfo(IAsyncConnectionProcessor::ResponseHandle handle_, mg_connection* connection_) :
                handle(std::move(handle_)), connection(connection_) {}
    };
}

struct TcpAsyncServerTransport::Impl
{
    std::string address;
    std::chrono::milliseconds networkTimeout;

    mg_mgr mgr;
    mg_connection* rootConnection;

    std::shared_ptr<IAsyncConnectionProcessor> connectionProcessor;


    bool closeRequested;
    std::thread workerThread;

    std::list<ResponseInfo> responses;

    std::hash<std::string> stringHasher;

    void thread_func();

    Impl(std::string address_, std::chrono::milliseconds networkTimeout_) :
            address(address_),
            networkTimeout(networkTimeout_),
            mgr(),
            rootConnection(nullptr),
            connectionProcessor(nullptr),
            closeRequested(false),
            workerThread(),
            responses(),
            stringHasher() {}
};

namespace
{
    void server_handler(struct mg_connection *nc, int event, void*)
    {
        auto* impl_ = reinterpret_cast<TcpAsyncServerTransport::Impl*>(nc->mgr->user_data);

        const std::string clientAddress = Mongoose::socket_to_string(nc->sa);

        switch (event)
        {
            case MG_EV_SEND:
            {
                log_debug(with_log_prefix("Sent data to ").append(clientAddress));
                break;
            }
            case MG_EV_ACCEPT:
            {
                log_debug(with_log_prefix("Client connected at ").append(clientAddress));
                impl_->connectionProcessor->open_connection(impl_->stringHasher(clientAddress));
                break;
            }
            case MG_EV_RECV:
            {
                log_debug(with_log_prefix("Received data from ").append(clientAddress));

                if (impl_->connectionProcessor != nullptr)
                {
                    std::vector<uint8_t> received(nc->recv_mbuf.buf, nc->recv_mbuf.buf + nc->recv_mbuf.len);
                    mbuf_remove(&nc->recv_mbuf, nc->recv_mbuf.len);

                    impl_->responses.push_back(
                            ResponseInfo(impl_->connectionProcessor->get_response(
                                    impl_->stringHasher(clientAddress), received), nc));
                }
                break;
            }
            case MG_EV_CLOSE:
            {
                log_debug(with_log_prefix("Connection at ")
                                  .append(Mongoose::socket_to_string(nc->sa))
                                  .append(" has been closed"));
                impl_->connectionProcessor->close_connection(impl_->stringHasher(clientAddress));
                break;
            }
            default: break;

        }
    }
}

void TcpAsyncServerTransport::Impl::thread_func()
{
    try
    {
        while (!closeRequested)
        {
            mg_mgr_poll(&mgr, MONGOOSE_POOL_INTERVAL);

            auto currentResponse = responses.begin();
            while (currentResponse != responses.end())
            {
                if (currentResponse->handle.wait_for(0s) == std::future_status::ready)
                {
                    log_debug(with_log_prefix("Sending response to ")
                                      .append(Mongoose::socket_to_string(currentResponse->connection->sa)));

                    auto responseHandle = currentResponse->handle.get();

                    mg_send(currentResponse->connection,
                            responseHandle.data(),
                            static_cast<int>(responseHandle.size()));

                    responses.erase(currentResponse++);
                }
                else
                {
                    ++currentResponse;
                }
            }
        }

        rootConnection = nullptr;
    }
    catch (const TransportException& e)
    {
        log_error(e.to_string());
    }
    catch (const std::exception& e)
    {
        log_error(with_log_prefix("Unexpected error: ").append( e.what()));
    }
}

TcpAsyncServerTransport::TcpAsyncServerTransport(const std::string& address, std::chrono::milliseconds networkTimeout) :
        impl_(new Impl(address, networkTimeout)) {}

void TcpAsyncServerTransport::register_request_processor(std::shared_ptr<IAsyncConnectionProcessor> requestProcessor)
{
    impl_->connectionProcessor = std::move(requestProcessor);
}

void TcpAsyncServerTransport::run()
{
    log_info(with_log_prefix("Starting background thread..."));
    if (impl_->rootConnection == nullptr)
    {
        impl_->closeRequested = false;

        mg_mgr_init(&impl_->mgr, this->impl_.get());
        impl_->rootConnection = mg_bind(&impl_->mgr, impl_->address.c_str(), server_handler);

        if (!impl_->rootConnection)
        {
            throw ConnectionException(std::string("Can't bind port at ").append(impl_->address));
        }

        impl_->workerThread = std::thread([this]()
        {
            impl_->thread_func();
        });
    }
    else
    {
        log_info(with_log_prefix("Trying to start TcpAsyncServer more than once before closing"));
    }
}

void TcpAsyncServerTransport::close()
{
    log_info(with_log_prefix("Closing connection..."));
    impl_->closeRequested = true;
    if (impl_->workerThread.joinable())
    {
        impl_->workerThread.join();
        impl_->rootConnection = nullptr;
    }
}

TcpAsyncServerTransport::~TcpAsyncServerTransport() = default;
