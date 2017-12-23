#include <webserver/WebServer.h>

#include <algorithm>
#include <fstream>
#include <iterator>
#include <vector>
#include <thread>
#include <atomic>
#include <mongoose.h>
#include <webserver/WebServerExceptions.h>


using namespace Dcdr::Server;

namespace Dcdr::Server
{
    struct WebServer::WebServerImpl
    {
    public:
        mg_mgr mongoose_manager_;
        std::string fs_root_;
        std::thread workerThread;
        std::atomic<bool> serverInterrupted;

        void process_request(mg_connection* connection, http_message *message);
    };
}

namespace
{
    const std::string API_URI_PREFIX("/api/");
    const std::string HEADER_HTML_DOC("Content-Type: text/plain");
    const int STATUS_OK(200);

    enum class HttpEvent
    {
        Unknown,
        Request
    };

    HttpEvent http_event_from_mongoose_event(int event)
    {
        if (event == MG_EV_HTTP_REQUEST)
        {
            return HttpEvent::Request;
        }

        return HttpEvent::Unknown;
    }

    void mongoose_event_handler(mg_connection* connection, int event, void* data)
    {
        switch(http_event_from_mongoose_event(event))
        {
            case HttpEvent::Request:
            {
                reinterpret_cast<WebServer::WebServerImpl*>(connection->mgr->user_data)->process_request(
                        connection, reinterpret_cast<http_message*>(data));
            }
            default:
            {
                return;
            }
        }
    }

    std::unique_ptr<WebServer::WebServerImpl> construct_web_server(int port, const std::string& fs_root)
    {
        std::unique_ptr<WebServer::WebServerImpl> server(new WebServer::WebServerImpl {});

        server->fs_root_ = fs_root;
        server->workerThread = std::thread();
        server->serverInterrupted = false;

        mg_mgr_init(&server->mongoose_manager_, server.get());

        auto connection = mg_bind(
                &server->mongoose_manager_,
                std::to_string(port).c_str(),
                mongoose_event_handler);

        if (connection == nullptr)
        {
            throw MongooseException("Can't bind port " + std::to_string(port));
        }

        mg_set_protocol_http_websocket(connection);

        return std::move(server);
    }
}


void WebServer::WebServerImpl::process_request(mg_connection* connection, http_message* message)
{
    std::string uri(message->uri.p, message->uri.len);
    if (std::equal(API_URI_PREFIX.cbegin(), API_URI_PREFIX.cend(), uri.cbegin()))
    {
        // Process api
    }
    else
    {
        std::string filePath = fs_root_ + uri;
        std::ifstream file(filePath);
        if (!file.is_open())
        {
            // log error?
            return;
        }

        std::vector<char> file_buffer;
        // implement caching?
        std::copy(std::istream_iterator<char>(file), std::istream_iterator<char>(), std::back_inserter(file_buffer));

        mg_send_head(connection, STATUS_OK, file_buffer.size(), HEADER_HTML_DOC.c_str());
        mg_send(connection, file_buffer.data(), static_cast<int>(file_buffer.size()));
    }
}

WebServer::WebServer(int port, const std::string& fs_root) :
    impl_(construct_web_server(port, fs_root)) {}

WebServer::~WebServer() = default;

void WebServer::run()
{
    impl_->serverInterrupted = false;
    impl_->workerThread = std::thread([&]()
    {
        for (;!impl_->serverInterrupted;)
        {
            mg_mgr_poll(&impl_->mongoose_manager_, 1000);
        }
    });

}

void WebServer::stop()
{
    impl_->serverInterrupted = true;
    impl_->workerThread.join();
}
