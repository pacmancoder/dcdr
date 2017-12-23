#pragma once

#include <string>
#include <memory>

namespace Dcdr::Server
{
    class WebServer
    {
    public:
        WebServer(int port, const std::string& fs_root);

        void run();
        void stop();

        ~WebServer();
    public:
        class WebServerImpl;

    private:
        std::unique_ptr<WebServerImpl> impl_;
    };

}