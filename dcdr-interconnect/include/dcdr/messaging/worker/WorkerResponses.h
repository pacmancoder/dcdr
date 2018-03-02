#pragma once

#include <dcdr/messaging/worker/WorkerInterconnectTypes.h>

namespace Dcdr::Interconnect
{
    /// @brief Base class for al worker requests.
    class WorkerResponse
    {
    public:
        explicit WorkerResponse(uint32_t nodeId);

        uint32_t get_node_id() const;
    private:
        uint32_t nodeId_;
    };

    class WorkerLoginResponse : public WorkerResponse
    {
    public:
        explicit WorkerLoginResponse(uint32_t nodeId);
    };

    class WorkerServerStatusResponse : public WorkerResponse
    {
    public:
        WorkerServerStatusResponse(uint32_t nodeId, Worker::ServerStatus status, const std::string& message = "");

        Worker::ServerStatus get_status() const;
        const std::string& get_message() const;

    private:
        Worker::ServerStatus status_;
        std::string message_;
    };

    class WorkerPollTasksResponse : public WorkerResponse
    {
    public:
        WorkerPollTasksResponse(uint32_t nodeId, const std::vector<Worker::TaskInfo>& tasks);

        const std::vector<Worker::TaskInfo>& get_tasks() const;

    private:
        std::vector<Worker::TaskInfo> tasks_;
    };

    class WorkerDownloadSceneResponse : public WorkerResponse
    {
    public:
        WorkerDownloadSceneResponse(
                uint32_t nodeId,
                uint32_t sceneId,
                uint64_t offset, // TODO: remove
                uint64_t bytesLeft,
                std::vector<uint8_t>&& data);

        uint32_t get_scene_id() const;
        uint64_t get_offset() const;
        uint64_t get_bytes_left() const;
        const std::vector<uint8_t>& get_data() const;

    private:
        uint32_t nodeId_;
        uint32_t sceneId_;
        uint64_t offset_;
        uint64_t bytesLeft_;
        std::vector<uint8_t> data_;
    };
}