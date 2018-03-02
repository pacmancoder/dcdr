#include <dcdr/server/core/ChunkTask.h>

using namespace Dcdr::Server;

ChunkTask::ChunkTask(uint32_t jobId, uint32_t nodeId, ChunkRect rect, uint32_t minIterations, uint32_t maxIterations) :
    jobId_(jobId),
    nodeId_(nodeId),
    timestamp_(std::chrono::system_clock::now()),
    rect_(rect),
    minIterations_(minIterations),
    maxIterations_(maxIterations) {}

std::chrono::milliseconds ChunkTask::get_duration() const
{
    return  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - timestamp_);
}

uint32_t ChunkTask::get_job_id() const
{
    return jobId_;
}

uint32_t ChunkTask::get_node_id() const
{
    return nodeId_;
}

uint32_t ChunkTask::get_min_iterations() const
{
    return minIterations_;
}

uint32_t ChunkTask::get_max_iterations() const
{
    return maxIterations_;
}

const ChunkRect ChunkTask::get_chunk_rect() const
{
    return rect_;
}
