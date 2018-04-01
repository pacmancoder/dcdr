#pragma once

#include <chrono>

namespace Dcdr::Utils
{
    class StopWatch
    {
    public:
        explicit StopWatch() :
                start_(std::chrono::system_clock::now()) {}

        void reset()
        {
            start_ = std::chrono::system_clock::now();
        }

        std::chrono::milliseconds duration()
        {
            return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start_);
        }

    private:
        std::chrono::time_point<std::chrono::system_clock> start_;
    };
}