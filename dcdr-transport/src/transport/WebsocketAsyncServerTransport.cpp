#include <dcdr/transport/WebsocketAsyncServerTransport.h>
#include <dcdr/utils/Timer.h>
#include <dcdr/logging/Logger.h>

#include <dcdr/transport/TransportExceptions.h>

#include <mongoose.h>
#include <thread>
#include <list>
#include <functional>
#include <map>

#include <iostream>


#include "private/MongooseUtils.h"

using namespace Dcdr::Transport;
using namespace Dcdr::Logging;
using namespace std::chrono_literals;

namespace
{
    const char* LOG_PREFIX = "[Transport][TcpAsyncServer] ";
    const int MONGOOSE_POOL_INTERVAL = 50;

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

struct WebsocketAsyncServerTransport::Impl
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

    std::map<size_t, uint32_t> connectionIds_;

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
    void server_handler(struct mg_connection *nc, int event, void* eventData)
    {
        auto* impl_ = reinterpret_cast<WebsocketAsyncServerTransport::Impl*>(nc->mgr->user_data);

        const std::string clientAddress = Mongoose::socket_to_string(nc->sa);

        switch (event)
        {
            case MG_EV_SEND:
            {
                log_trace(LOG_PREFIX, "Sent data to ", clientAddress);
                break;
            }
            case MG_EV_ACCEPT:
            {

                log_debug(LOG_PREFIX, "Client connected at ", clientAddress);

                impl_->connectionIds_.emplace(impl_->stringHasher(clientAddress),
                        impl_->connectionProcessor->open_connection());
                break;
            }
            case MG_EV_WEBSOCKET_FRAME:
            {
                const auto* receivedMessage = reinterpret_cast<const websocket_message*>(eventData);
                if ((receivedMessage->flags & 0x0F) != WEBSOCKET_OP_BINARY)
                {
                    break;
                }

                log_trace(LOG_PREFIX, "Received data from ", clientAddress, " with size ", receivedMessage->size);

                if (impl_->connectionProcessor != nullptr)
                {
                    std::vector<uint8_t> received(receivedMessage->data, receivedMessage->data + receivedMessage->size);

                    impl_->responses.push_back(
                            ResponseInfo(impl_->connectionProcessor->get_response(
                                    impl_->connectionIds_.at(impl_->stringHasher(clientAddress)), received), nc));
                }
                break;
            }
            case MG_EV_CLOSE:
            {
                log_debug(LOG_PREFIX, "Connection at ", Mongoose::socket_to_string(nc->sa), " has been closed");

                auto connectionHash = impl_->stringHasher(clientAddress);

                impl_->connectionProcessor->close_connection(
                        impl_->connectionIds_.at(connectionHash));

                impl_->connectionIds_.erase(connectionHash);
                break;
            }
            default: break;

        }
    }
}

void WebsocketAsyncServerTransport::Impl::thread_func()
{
    try
    {
        while (!closeRequested)
        {
            mg_mgr_poll(&mgr, MONGOOSE_POOL_INTERVAL);

            auto currentResponse = responses.begin();
            while (currentResponse != responses.end())
            {
                if (!currentResponse->handle.valid())
                {
                    responses.erase(currentResponse++);
                }
                else if (currentResponse->handle.wait_for(0s) == std::future_status::ready)
                {
                    auto responseHandle = currentResponse->handle.get();

                    log_trace(LOG_PREFIX, "Sending response with size ", responseHandle.size(), " to ",
                        Mongoose::socket_to_string(currentResponse->connection->sa));

                    mg_send_websocket_frame(
                            currentResponse->connection,
                            WEBSOCKET_OP_BINARY,
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
        log_error(LOG_PREFIX, "Unexpected error: ", e.what());
    }
}

WebsocketAsyncServerTransport::WebsocketAsyncServerTransport(const std::string& address, std::chrono::milliseconds networkTimeout) :
        impl_(new Impl(address, networkTimeout)) {}

void WebsocketAsyncServerTransport::register_request_processor(std::shared_ptr<IAsyncConnectionProcessor> requestProcessor)
{
    impl_->connectionProcessor = std::move(requestProcessor);
}

void WebsocketAsyncServerTransport::run()
{
    if (impl_->rootConnection == nullptr)
    {
        impl_->closeRequested = false;

        mg_mgr_init(&impl_->mgr, this->impl_.get());
        impl_->rootConnection = mg_bind(&impl_->mgr, impl_->address.c_str(), server_handler);
        mg_set_protocol_http_websocket(impl_->rootConnection );

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
        log_warning(LOG_PREFIX, "Trying to start TcpAsyncServer more than once before closing");
    }
}

void WebsocketAsyncServerTransport::close()
{
    impl_->closeRequested = true;
    if (impl_->workerThread.joinable())
    {
        impl_->workerThread.join();
        impl_->rootConnection = nullptr;
    }
}

WebsocketAsyncServerTransport::~WebsocketAsyncServerTransport() = default;
