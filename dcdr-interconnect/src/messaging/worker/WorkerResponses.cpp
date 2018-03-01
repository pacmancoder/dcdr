#include <dcdr/messaging/worker/WorkerResponses.h>

using namespace Dcdr::Interconnect;

WorkerResponse::WorkerResponse(uint32_t nodeId) :
    nodeId_(nodeId) {}

uint32_t WorkerResponse::get_node_id() const
{
    return nodeId_;
}

WorkerLoginResponse::WorkerLoginResponse(uint32_t nodeId) :
        WorkerResponse(nodeId) {}

WorkerServerStatusResponse::WorkerServerStatusResponse(
        uint32_t nodeId, Worker::ServerStatus status, const std::string &message) :
    WorkerResponse(nodeId), status_(status), message_(message) {}

Worker::ServerStatus WorkerServerStatusResponse::get_status() const
{
    return status_;
}

const std::string &WorkerServerStatusResponse::get_message() const
{
    return message_;
}

WorkerPollTasksResponse::WorkerPollTasksResponse(uint32_t nodeId, const std::vector<Worker::TaskInfo> &tasks) :
    WorkerResponse(nodeId), tasks_(tasks) {}

const std::vector<Worker::TaskInfo> &WorkerPollTasksResponse::get_tasks() const
{
    return tasks_;
}

WorkerDownloadSceneResponse::WorkerDownloadSceneResponse(
        uint32_t nodeId, uint32_t sceneId, uint64_t offset, uint64_t bytesLeft, std::vector<uint8_t> &&data) :
    WorkerResponse(nodeId), sceneId_(sceneId), offset_(offset), bytesLeft_(bytesLeft), data_(std::move(data)) {}

uint32_t WorkerDownloadSceneResponse::get_scene_id() const
{
    return sceneId_;
}

uint64_t WorkerDownloadSceneResponse::get_offset() const
{
    return offset_;
}

uint64_t WorkerDownloadSceneResponse::get_bytes_left() const
{
    return bytesLeft_;
}

const std::vector<uint8_t> &WorkerDownloadSceneResponse::get_data() const
{
    return data_;
}
