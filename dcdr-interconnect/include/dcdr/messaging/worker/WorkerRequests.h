#pragma once

#include <dcdr/messaging/worker/WorkerInterconnectTypes.h>

#include <vector>

namespace Dcdr::Interconnect
{
    /// @brief Base class for al worker requests.
    class WorkerRequest
    {
    public:
        explicit WorkerRequest(uint32_t nodeId);

        uint32_t get_node_id() const;
    private:
        uint32_t nodeId_;
    };

    class WorkerLoginRequest : public WorkerRequest
    {
    public:
        WorkerLoginRequest(
                const std::string& name,
                const std::string& token);

        const std::string get_name() const;
        const std::string get_token() const;

    private:
        std::string name_;
        std::string token_;
    };

    class WorkerLogoutRequest : public WorkerRequest
    {
    public:
        explicit WorkerLogoutRequest(uint32_t nodeId);
    };

    class WorkerSendHardwareInfoRequest : public WorkerRequest
    {
    public:
        WorkerSendHardwareInfoRequest(
                uint32_t nodeId,
                const std::vector<PropertyPair>& properties);

        const std::vector<PropertyPair>& get_properties() const;
    private:
        std::vector<PropertyPair> properties_;
    };

    class WorkerPollTasksRequest : public WorkerRequest
    {
    public:
        explicit WorkerPollTasksRequest(uint32_t nodeId);
    };

    class WorkerCommitTasksRequest : public WorkerRequest
    {
    public:
        WorkerCommitTasksRequest(uint32_t nodeId, std::vector<Worker::TaskArtifact>&& artifacts);

        const std::vector<Worker::TaskArtifact>& get_artifacts() const;
    private:
        std::vector<Worker::TaskArtifact> artifacts_;
    };

    class WorkerDownloadSceneRequest : public WorkerRequest
    {
    public:
        WorkerDownloadSceneRequest(uint32_t nodeId, uint32_t sceneId, uint64_t offset);

        uint32_t get_scene_id() const;
        uint64_t get_offset() const;

    private:
        uint32_t scene_;
        uint64_t offset_;
    };
}