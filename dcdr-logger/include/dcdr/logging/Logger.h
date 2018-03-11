#pragma once

#include <dcdr/logging/ILogWriter.h>
#include <vector>
#include <memory>
#include <mutex>
#include <sstream>

namespace Dcdr::Logging
{
    class Logger
    {
    public:
        static Logger& get_instance();

        void add_log_writer(std::unique_ptr<ILogWriter> logWriter);
        void log(LogCategory messageType, const std::string& message);

        void enable_trace();
        bool is_trace_enabled() const;

        void enable_debug();
        bool is_debug_enabled() const;

    private:
        Logger();

    private:
        std::vector<std::unique_ptr<ILogWriter>> logWriters_;
        std::mutex logMutex_;
        bool traceEnabled_;
        bool debugEnabled_;
    };

    template <typename Arg>
    void __write_to_strstream(std::stringstream& stream, Arg&& arg)
    {
        stream << std::forward<Arg>(arg);
    }

    template <typename Arg>
    void __write_varargs_to_strstream(std::stringstream& stream, Arg&& arg)
    {
        __write_to_strstream(stream, std::forward<Arg>(arg));
    }

    template <typename Arg, typename... Args>
    void __write_varargs_to_strstream(std::stringstream& stream, Arg&& arg, Args&&... args)
    {
        __write_to_strstream(stream, arg);

        __write_varargs_to_strstream(stream, std::forward<Args>(args)...);
    }

    template <typename... Args>
    void __log_internal(LogCategory category, Args&&... args)
    {
        std::stringstream stream;
        __write_varargs_to_strstream(stream, std::forward<Args>(args)...);
        Logger::get_instance().log(category, stream.str());
    }

    // Macro are used to avoid argument evaluation if current log level disabled

    #define log_error(...) Dcdr::Logging::__log_internal(LogCategory::Error, __VA_ARGS__)
    #define log_warning(...) Dcdr::Logging::__log_internal(LogCategory::Warning, __VA_ARGS__)
    #define log_info(...) Dcdr::Logging::__log_internal(LogCategory::Info, __VA_ARGS__)
    #define log_debug(...) if (Dcdr::Logging::Logger::get_instance().is_debug_enabled()) \
        Dcdr::Logging::__log_internal(LogCategory::Debug, __VA_ARGS__)
    #define log_trace(...) if (Dcdr::Logging::Logger::get_instance().is_trace_enabled()) \
        Dcdr::Logging::__log_internal(LogCategory::Trace, __VA_ARGS__)
}
