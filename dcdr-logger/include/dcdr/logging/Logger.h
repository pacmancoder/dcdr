#pragma once

#include <dcdr/logging/ILogWriter.h>
#include <vector>
#include <memory>
#include <mutex>

namespace Dcdr::Logging
{
    class Logger
    {
    public:
        static Logger& get_instance();

        void add_log_writer(std::unique_ptr<ILogWriter> logWriter);
        void log(ILogWriter::MessageType messageType, const std::string& message);

    private:
        std::vector<std::unique_ptr<ILogWriter>> log_writers_;
        std::mutex log_mutex_;
    };

    // convenient functions to log information using current logger
    extern void log_error(const std::string& message);
    extern void log_warning(const std::string& message);
    extern void log_info(const std::string& message);
    extern void log_debug(const std::string& message);
}