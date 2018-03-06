#include <dcdr/logging/Logger.h>

using namespace Dcdr::Logging;

Logger::Logger() :
    logWriters_(),
    logMutex_(),
    traceEnabled_(false) {}

Logger& Logger::get_instance()
{
    static Logger logger;
    return logger;
}

void Logger::enable_trace()
{
    traceEnabled_ = true;
}

bool Logger::is_trace_enabled()
{
    return traceEnabled_;
}

void Logger::add_log_writer(std::unique_ptr<ILogWriter> logWriter)
{
    std::lock_guard<std::mutex> lock_guard(logMutex_);

    logWriters_.push_back(std::move(logWriter));
}

void Logger::log(LogCategory messageType, const std::string& message)
{
    std::lock_guard<std::mutex> lock_guard(logMutex_);

    for (auto& log_writer : logWriters_)
    {
        log_writer->write(messageType, message);
    }
}