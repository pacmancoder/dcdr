#include <dcdr/messaging/commander/CommanderResponses.h>

using namespace Dcdr::Interconnect;

CommanderGetJobListResponse::CommanderGetJobListResponse(std::vector<Commander::Job> jobs) :
    jobs_(std::move(jobs)) {}

const std::vector<Commander::Job>& CommanderGetJobListResponse::get_jobs() const
{
    return jobs_;
}

ACommanderJobResponse::ACommanderJobResponse(uint32_t id) :
    id_(id) {}

uint32_t ACommanderJobResponse::get_job_id() const
{
    return id_;
}

CommanderGetJobInfoResponse::CommanderGetJobInfoResponse(uint32_t id, std::vector<Commander::PropertyPair> properties) :
    ACommanderJobResponse(id), properties_(std::move(properties)) {}

const std::vector<Commander::PropertyPair>& CommanderGetJobInfoResponse::get_job_info() const
{
    return properties_;
}

CommanderGetJobPreviewResponse::CommanderGetJobPreviewResponse(uint32_t id, std::vector<uint8_t> data) :
    ACommanderJobResponse(id), data_(std::move(data)) {}

const std::vector<uint8_t>& CommanderGetJobPreviewResponse::get_preview() const
{
    return data_;
}

CommanderGetJobArtifactResponse::CommanderGetJobArtifactResponse(uint32_t id, std::vector<uint8_t> data) :
    ACommanderJobResponse(id), data_(std::move(data)) {}

const std::vector<uint8_t>& CommanderGetJobArtifactResponse::get_artifact() const
{
    return data_;
}

CommanderGetSceneListResponse::CommanderGetSceneListResponse(std::vector<Commander::Scene> scenes) :
    scenes_(std::move(scenes)) {}

const std::vector<Commander::Scene>& CommanderGetSceneListResponse::get_scenes() const
{
    return scenes_;
}

CommanderGetNodeListResponse::CommanderGetNodeListResponse(std::vector<Commander::Node> nodes) :
    nodes_(nodes) {}

const std::vector<Commander::Node>& CommanderGetNodeListResponse::get_nodes() const
{
    return nodes_;
}

ACommanderNodeResponse::ACommanderNodeResponse(uint32_t id) :
    id_(id) {}

uint32_t ACommanderNodeResponse::get_node_id() const
{
    return id_;
}

CommanderGetNodeInfoResponse::CommanderGetNodeInfoResponse(
        uint32_t id, std::vector<Commander::PropertyPair> properties) :
    ACommanderNodeResponse(id), properies_(std::move(properties)) {}

const std::vector<Commander::PropertyPair>& CommanderGetNodeInfoResponse::get_node_info() const
{
    return properies_;
}

CommanderDoShowErrorResponse::CommanderDoShowErrorResponse(
        Commander::CommanderErrorKind errorKind, const std::string& message) :
    errorKind_(errorKind), message_(message) {}

const std::string& CommanderDoShowErrorResponse::get_message() const
{
    return message_;
}

Commander::CommanderErrorKind CommanderDoShowErrorResponse::get_error_kind() const
{
    return errorKind_;
}

