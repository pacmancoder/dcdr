#include <dcdr/messaging/commander/CommanderRequests.h>

using namespace Dcdr::Interconnect;

ACommanderJobRequest::ACommanderJobRequest(uint32_t jobId) :
        jobId_(jobId) {}

uint32_t ACommanderJobRequest::get_job_id() const { return jobId_; }

CommanderGetJobInfoRequest::CommanderGetJobInfoRequest(uint32_t jobId) :
        ACommanderJobRequest(jobId) {}

CommanderSetJobStateRequest::CommanderSetJobStateRequest(uint32_t jobId, JobState jobState) :
        ACommanderJobRequest(jobId), jobState_(jobState) {}

JobState CommanderSetJobStateRequest::get_job_state() const { return jobState_; }

CommanderGetJobPreviewRequest::CommanderGetJobPreviewRequest(uint32_t jobId, uint8_t mipmapLevel) :
        ACommanderJobRequest(jobId), mipmapLevel_(mipmapLevel) {}

uint8_t CommanderGetJobPreviewRequest::get_mipmap_level() const { return mipmapLevel_; }

CommanderGetJobArtifactRequest::CommanderGetJobArtifactRequest(uint32_t jobId) :
        ACommanderJobRequest(jobId) {}

CommanderAddJobRequest::CommanderAddJobRequest(uint32_t sceneId, float scale) :
        sceneId_(sceneId), scale_(scale) {}

uint32_t CommanderAddJobRequest::get_scene_id() const { return sceneId_; }

float CommanderAddJobRequest::get_scale() const { return scale_; }

ACommanderNodeRequest::ACommanderNodeRequest(uint32_t nodeId) :
        nodeId_(nodeId) {}

uint32_t ACommanderNodeRequest::get_node_id() const { return nodeId_; }

CommanderGetNodeInfoRequest::CommanderGetNodeInfoRequest(uint32_t nodeId) :
        ACommanderNodeRequest(nodeId) {}

CommanderSetNodeStateRequest::CommanderSetNodeStateRequest(uint32_t nodeId, NodeState nodeState) :
        ACommanderNodeRequest(nodeId), nodeState_(nodeState) {}

NodeState CommanderSetNodeStateRequest::get_node_state() const { return nodeState_; }
