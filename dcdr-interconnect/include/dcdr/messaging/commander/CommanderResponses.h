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
        CommanderGetJobInfoResponse(uint32_t id, std::vector<Commander::PropertyPair> properties);

        const std::vector<Commander::PropertyPair>& get_job_info() const;

    private:
        std::vector<Commander::PropertyPair> properties_;
    };

    class CommanderGetJobPreviewResponse : public ACommanderJobResponse
    {
    public:
        CommanderGetJobPreviewResponse(uint32_t id, std::vector<uint8_t> data);

        const std::vector<uint8_t>& get_preview() const;

    private:
        std::vector<uint8_t> data_;
    };

    class CommanderGetJobArtifactResponse : public ACommanderJobResponse
    {
    public:
        CommanderGetJobArtifactResponse(uint32_t id, std::vector<uint8_t> data);

        const std::vector<uint8_t>& get_artifact() const;

    private:
        std::vector<uint8_t> data_;
    };

    class CommanderDoJobListUpdateResponse {};

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
        CommanderGetNodeInfoResponse(uint32_t id, std::vector<Commander::PropertyPair> properties);

        const std::vector<Commander::PropertyPair>& get_node_info() const;

    private:
        std::vector<Commander::PropertyPair> properies_;
    };

    class CommanderDoNodeListUpdateResponse {};

    class CommanderDoShowErrorResponse
    {
    public:
        CommanderDoShowErrorResponse(Commander::CommanderErrorKind errorKind, const std::string& message);

        const std::string& get_message() const;
        Commander::CommanderErrorKind get_error_kind() const;

    private:
        Commander::CommanderErrorKind errorKind_;
        std::string message_;
    };
}