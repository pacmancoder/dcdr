#include <dcdr/messaging/worker/WorkerRequests.h>

using namespace Dcdr::Interconnect;

WorkerRequest::WorkerRequest(uint32_t nodeId) :
    nodeId_(nodeId) {}

uint32_t WorkerRequest::get_node_id() const
{
    return nodeId_;
}

WorkerLoginRequest::WorkerLoginRequest(const std::string &name, const std::string &token) :
    WorkerRequest(0), name_(name), token_(token) {}

const std::string WorkerLoginRequest::get_name() const
{
    return name_;
}

const std::string WorkerLoginRequest::get_token() const
{
    return token_;
}

WorkerLogoutRequest::WorkerLogoutRequest(uint32_t nodeId) :
        WorkerRequest(nodeId) {}

WorkerSendHardwareInfoRequest::WorkerSendHardwareInfoRequest(
        uint32_t nodeId, const std::vector<PropertyPair> &properties) :
    WorkerRequest(nodeId), properties_(properties) {}

const std::vector<PropertyPair> &WorkerSendHardwareInfoRequest::get_properties() const
{
    return properties_;
}

WorkerPollTasksRequest::WorkerPollTasksRequest(uint32_t nodeId) :
        WorkerRequest(nodeId) {}

WorkerCommitTasksRequest::WorkerCommitTasksRequest(
        uint32_t nodeId, std::vector<Worker::TaskArtifact> &&artifacts) :
    WorkerRequest(nodeId), artifacts_(std::move(artifacts)) {}

const std::vector<Worker::TaskArtifact>& WorkerCommitTasksRequest::get_artifacts() const
{
    return artifacts_;
}

WorkerDownloadSceneRequest::WorkerDownloadSceneRequest(uint32_t nodeId, uint32_t sceneId, uint64_t offset) :
    WorkerRequest(nodeId), scene_(sceneId), offset_(offset) {}

uint32_t WorkerDownloadSceneRequest::get_scene_id() const
{
    return scene_;
}

uint64_t WorkerDownloadSceneRequest::get_offset() const
{
    return offset_;
}
