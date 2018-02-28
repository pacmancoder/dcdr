#include <dcdr/messaging/commander/CommanderResponses.h>

using namespace Dcdr::Interconnect;

CommanderGetJobListResponse::CommanderGetJobListResponse(std::vector<Commander::Job> jobs) :
    jobs_(std::move(jobs)) {}

const std::vector<Commander::Job>& CommanderGetJobListResponse::get_jobs() const { return jobs_; }

ACommanderJobResponse::ACommanderJobResponse(uint32_t id) :
    id_(id) {}

uint32_t ACommanderJobResponse::get_job_id() const { return id_; }

CommanderGetJobInfoResponse::CommanderGetJobInfoResponse(uint32_t id, std::vector<PropertyPair> properties) :
    ACommanderJobResponse(id), properties_(std::move(properties)) {}

const std::vector<PropertyPair>& CommanderGetJobInfoResponse::get_job_info() const { return properties_; }

CommanderGetJobArtifactResponse::CommanderGetJobArtifactResponse(
        uint32_t id,
        Commander::ArtifactFormat format,
        uint16_t width,
        uint16_t height,
        std::vector<uint8_t> data) :
    ACommanderJobResponse(id),
    format_(format),
    width_(width),
    height_(height),
    data_(std::move(data)) {}

Commander::ArtifactFormat CommanderGetJobArtifactResponse::get_format() const { return format_; }

uint16_t CommanderGetJobArtifactResponse::get_width() const { return width_; }

uint16_t CommanderGetJobArtifactResponse::get_height() const { return height_; }

const std::vector<uint8_t>& CommanderGetJobArtifactResponse::get_data() const { return data_; }

CommanderGetSceneListResponse::CommanderGetSceneListResponse(std::vector<Commander::Scene> scenes) :
    scenes_(std::move(scenes)) {}

const std::vector<Commander::Scene>& CommanderGetSceneListResponse::get_scenes() const { return scenes_; }

CommanderGetNodeListResponse::CommanderGetNodeListResponse(std::vector<Commander::Node> nodes) :
    nodes_(nodes) {}

const std::vector<Commander::Node>& CommanderGetNodeListResponse::get_nodes() const { return nodes_; }

ACommanderNodeResponse::ACommanderNodeResponse(uint32_t id) :
    id_(id) {}

uint32_t ACommanderNodeResponse::get_node_id() const { return id_; }

CommanderGetNodeInfoResponse::CommanderGetNodeInfoResponse(
        uint32_t id, std::vector<PropertyPair> properties) :
    ACommanderNodeResponse(id), properies_(std::move(properties)) {}

const std::vector<PropertyPair>& CommanderGetNodeInfoResponse::get_node_info() const { return properies_; }

CommanderErrorResponse::CommanderErrorResponse(
        Commander::CommanderErrorKind errorKind, const std::string& message) :
    errorKind_(errorKind), message_(message) {}

const std::string& CommanderErrorResponse::get_message() const { return message_; }

Commander::CommanderErrorKind CommanderErrorResponse::get_error_kind() const { return errorKind_; }

CommanderGetServerStatusResponse::CommanderGetServerStatusResponse(
        uint64_t scenesLastModifiedTimestamp,
        uint64_t jobsLastModifiedTimestamp,
        uint64_t nodesLastModifiedTimestamp) :
    scenesLastModifiedTimestamp_(scenesLastModifiedTimestamp),
    jobsLastModifiedTimestamp_(jobsLastModifiedTimestamp),
    nodesLastModifiedTimestamp_(nodesLastModifiedTimestamp) {}

uint64_t CommanderGetServerStatusResponse::get_scenes_last_modified_timestamp() const { return scenesLastModifiedTimestamp_; }

uint64_t CommanderGetServerStatusResponse::get_nodes_last_modified_timestamp() const { return nodesLastModifiedTimestamp_; }

uint64_t CommanderGetServerStatusResponse::get_jobs_last_modified_timestamp() const { return jobsLastModifiedTimestamp_; }