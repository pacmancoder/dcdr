#pragma once

#include <chrono>

namespace Dcdr::Utils
{
    class Timer
    {
    public:
        explicit Timer(std::chrono::milliseconds interval) :
                start_(std::chrono::system_clock::now()),
                interval_(interval) {}

        bool elapsed()
        {
            return std::chrono::system_clock::now() - start_ >= interval_;
        }

    private:
        std::chrono::time_point<std::chrono::system_clock> start_;
        std::chrono::milliseconds interval_;
    };
}