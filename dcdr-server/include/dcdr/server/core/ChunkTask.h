#pragma once

#include <cstdint>
#include <chrono>

#include <dcdr/server/core/Chunk.h>

namespace Dcdr::Server
{
    class ChunkTask
    {
    public:
        ChunkTask(uint32_t jobId, uint32_t nodeId, ChunkRect rect, uint32_t minIterations, uint32_t maxIterations);
        ChunkTask(const ChunkTask& rhs) = default;
        ChunkTask(ChunkTask&& rhs) = default;

        std::chrono::milliseconds get_duration() const;

        uint32_t get_job_id() const;
        uint32_t get_node_id() const;
        const ChunkRect get_chunk_rect() const;
        uint32_t get_min_iterations() const;
        uint32_t get_max_iterations() const;

    private:
        uint32_t jobId_;
        uint32_t nodeId_;
        std::chrono::time_point<std::chrono::system_clock> timestamp_;

        ChunkRect rect_;
        uint32_t minIterations_;
        uint32_t maxIterations_;
    };
}