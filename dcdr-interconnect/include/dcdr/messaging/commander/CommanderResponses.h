#pragma once

#include <vector>
#include <dcdr/messaging/commander/CommanderInterconnectTypes.h>

namespace Dcdr::Interconnect
{
    class CommanderGetJobListResponse
    {
    public:
        explicit CommanderGetJobListResponse(std::vector<Commander::Job> jobs);

        const std::vector<Commander::Job>& get_jobs() const;

    private:
        std::vector<Commander::Job> jobs_;
    };

    class ACommanderJobResponse
    {
    public:
        explicit ACommanderJobResponse(uint32_t id);

        uint32_t get_job_id() const;

        virtual ~ACommanderJobResponse() = default;
    private:
        uint32_t id_;
    };

    class CommanderGetJobInfoResponse : public ACommanderJobResponse
    {
    public:
        CommanderGetJobInfoResponse(uint32_t id, std::vector<PropertyPair> properties);

        const std::vector<PropertyPair>& get_job_info() const;

    private:
        std::vector<PropertyPair> properties_;
    };

    class CommanderGetJobArtifactResponse : public ACommanderJobResponse
    {
    public:
        CommanderGetJobArtifactResponse(
                uint32_t id,
                Commander::ArtifactFormat format,
                uint16_t width,
                uint16_t height,
                std::vector<uint8_t> data);

        Commander::ArtifactFormat get_format() const;
        uint16_t get_width() const;
        uint16_t get_height() const;
        const std::vector<uint8_t>& get_data() const;

    private:
        Commander::ArtifactFormat format_;
        uint16_t width_;
        uint16_t height_;
        std::vector<uint8_t> data_;
    };

    class CommanderGetSceneListResponse
    {
    public:
        explicit CommanderGetSceneListResponse(std::vector<Commander::Scene> scenes);

        const std::vector<Commander::Scene>& get_scenes() const;

    private:
        std::vector<Commander::Scene> scenes_;
    };

    class CommanderGetNodeListResponse
    {
    public:
        explicit CommanderGetNodeListResponse(std::vector<Commander::Node> nodes);

        const std::vector<Commander::Node>& get_nodes() const;

    private:
        std::vector<Commander::Node> nodes_;
    };

    class ACommanderNodeResponse
    {
    public:
        explicit ACommanderNodeResponse(uint32_t id);

        uint32_t get_node_id() const;

        virtual ~ACommanderNodeResponse() = default;

    private:
        uint32_t id_;
    };

    class CommanderGetNodeInfoResponse : public ACommanderNodeResponse
    {
    public:
        CommanderGetNodeInfoResponse(uint32_t id, std::vector<PropertyPair> properties);

        const std::vector<PropertyPair>& get_node_info() const;

    private:
        std::vector<PropertyPair> properies_;
    };

    class CommanderErrorResponse
    {
    public:
        CommanderErrorResponse(Commander::CommanderErrorKind errorKind, const std::string& message = "");

        const std::string& get_message() const;
        Commander::CommanderErrorKind get_error_kind() const;

    private:
        Commander::CommanderErrorKind errorKind_;
        std::string message_;
    };

    class CommanderGetServerStatusResponse
    {
    public:
        CommanderGetServerStatusResponse(
                uint64_t scenesLastModifiedTimestamp,
                uint64_t jobsLastModifiedTimestamp,
                uint64_t nodesLastModifiedTimestamp);

        uint64_t get_scenes_last_modified_timestamp() const;
        uint64_t get_nodes_last_modified_timestamp() const;
        uint64_t get_jobs_last_modified_timestamp() const;

    private:
        uint64_t scenesLastModifiedTimestamp_;
        uint64_t jobsLastModifiedTimestamp_;
        uint64_t nodesLastModifiedTimestamp_;
    };
}