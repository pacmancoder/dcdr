#include <dcdr/logging/Logger.h>

using namespace Dcdr::Logging;

Logger& Logger::get_instance()
{
    static Logger logger;
    return logger;
}

void Logger::add_log_writer(std::unique_ptr<ILogWriter> logWriter)
{
    std::lock_guard lock_guard(log_mutex_);

    log_writers_.push_back(std::move(logWriter));
}
void Logger::log(ILogWriter::MessageType messageType, const std::string& message)
{
    std::lock_guard lock_guard(log_mutex_);

    for (auto& log_writer : log_writers_)
    {
        log_writer->write(messageType, message);
    }
}

void Dcdr::Logging::log_error(const std::string& message)
{
    Logger::get_instance().log(ILogWriter::MessageType::Error, message);
}

void Dcdr::Logging::log_warning(const std::string& message)
{
    Logger::get_instance().log(ILogWriter::MessageType::Warning, message);
}

void Dcdr::Logging::log_info(const std::string& message)
{
    Logger::get_instance().log(ILogWriter::MessageType::Info, message);
}

void Dcdr::Logging::log_debug(const std::string& message)
{
    Logger::get_instance().log(ILogWriter::MessageType::Debug, message);
}