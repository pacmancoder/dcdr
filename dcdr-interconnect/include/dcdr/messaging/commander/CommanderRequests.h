#pragma once

#include <cstdint>
#include <dcdr/messaging/commander/CommanderInterconnectTypes.h>

namespace Dcdr::Interconnect
{
    class CommanderGetJobListRequest {};

    class ACommanderJobRequest
    {
    public:
        explicit ACommanderJobRequest(uint32_t jobId);

        uint32_t get_job_id() const;

    private:
        uint32_t jobId_;
    };

    class CommanderGetJobInfoRequest : public ACommanderJobRequest
    {
    public:
        explicit CommanderGetJobInfoRequest(uint32_t jobId);
    };

    class CommanderGetJobPreviewRequest: public ACommanderJobRequest
    {
    public:
        CommanderGetJobPreviewRequest(uint32_t jobId, uint8_t mipmapLevel);

        uint8_t get_mipmap_level() const;

    private:
        uint8_t mipmapLevel_;
    };

    class CommanderGetJobArtifactRequest : public ACommanderJobRequest
    {
    public:
        explicit CommanderGetJobArtifactRequest(uint32_t jobId);
    };

    class CommanderSetJobStateRequest : public ACommanderJobRequest
    {
    public:
        CommanderSetJobStateRequest(uint32_t jobId, Commander::JobState jobState);

        Commander::JobState get_job_state() const;

    private:
        Commander::JobState jobState_;
    };

    class CommanderAddJobRequest
    {
    public:
        CommanderAddJobRequest(uint32_t sceneId, float scale);

        uint32_t get_scene_id() const;
        float get_scale() const;

    private:
        uint32_t sceneId_;
        float scale_;
    };

    class CommanderGetSceneListRequest {};

    class CommanderGetNodeListRequest {};

    class ACommanderNodeRequest
    {
    public:
        explicit ACommanderNodeRequest(uint32_t nodeId);

        uint32_t get_node_id() const;

    private:
        uint32_t nodeId_;
    };

    class CommanderGetNodeInfoRequest : public ACommanderNodeRequest
    {
    public:
        explicit CommanderGetNodeInfoRequest(uint32_t nodeId);
    };

    class CommanderSetNodeStateRequest : public ACommanderNodeRequest
    {
    public:
        CommanderSetNodeStateRequest(uint32_t nodeId, Commander::NodeState nodeState);

        Commander::NodeState get_node_state() const;

    private:
        Commander::NodeState nodeState_;
    };
}