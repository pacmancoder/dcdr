#pragma once

#include <cstdint>
#include <chrono>

#include <dcdr/server/Chunk.h>

namespace Dcdr::Server
{
    class Work
    {
    public:
        Work(uint32_t jobId, uint32_t nodeId, ChunkRect rect, uint32_t minIterations, uint32_t maxIterations);

        std::chrono::milliseconds get_duration();

        uint32_t get_job_id();
        uint32_t get_node_id();
        uint32_t get_min_iterations();
        uint32_t get_max_iterations();

    private:
        uint32_t jobId_;
        uint32_t nodeId_;
        std::chrono::time_point<std::chrono::system_clock> timestamp_;

        ChunkRect rect_;
        uint32_t minIterations_;
        uint32_t maxIterations_;
    };
}