#include <dcdr/server/Work.h>

using namespace Dcdr::Server;

Work::Work(uint32_t jobId, uint32_t nodeId, ChunkRect rect, uint32_t minIterations, uint32_t maxIterations) :
    jobId_(jobId),
    nodeId_(nodeId),
    timestamp_(std::chrono::system_clock::now()),
    rect_(rect),
    minIterations_(minIterations),
    maxIterations_(maxIterations) {}

std::chrono::milliseconds Work::get_duration()
{
    return  std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - timestamp_);
}

uint32_t Work::get_job_id()
{
    return jobId_;
}

uint32_t Work::get_node_id()
{
    return nodeId_;
}

uint32_t Work::get_min_iterations()
{
    return minIterations_;
}

uint32_t Work::get_max_iterations()
{
    return maxIterations_;
}
