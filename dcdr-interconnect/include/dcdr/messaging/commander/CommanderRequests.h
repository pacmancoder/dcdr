#pragma once

#include <cstdint>
#include <dcdr/messaging/commander/ACommanderRequestParcel.h>
#include <dcdr/messaging/commander/ACommanderRequestParcelDispatcher.h>
#include <dcdr/messaging/commander/CommanderCommandData.h>

namespace Dcdr::Interconnect
{
    class AParcelSerializer;
    class ACommanderRequestParcelDispatcher;

    class CommanderGetJobListRequest : public ACommanderRequestParcel
    {
    public:
        SerializedParcel serialize(AParcelSerializer& serializer) const override;
        ParcelHandle dispatch(ACommanderRequestParcelDispatcher& dispatcher) const override;
    };

    class ACommanderJobRequest : public ACommanderRequestParcel
    {
    public:
        ACommanderJobRequest(uint32_t jobId);

        uint32_t get_job_id() const;
    private:
        uint32_t jobId_;
    };

    class CommanderGetJobInfoRequest : public ACommanderJobRequest
    {
    public:
        CommanderGetJobInfoRequest(uint32_t jobId);

        SerializedParcel serialize(AParcelSerializer& serializer) const override;
        ParcelHandle dispatch(ACommanderRequestParcelDispatcher& dispatcher) const override;
    };

    class CommanderGetJobPreviewRequest: public ACommanderJobRequest
    {
    public:
        CommanderGetJobPreviewRequest(uint32_t jobId, uint8_t mipmapLevel);

        SerializedParcel serialize(AParcelSerializer& serializer) const override;
        ParcelHandle dispatch(ACommanderRequestParcelDispatcher& dispatcher) const override;

        uint8_t get_mipmap_level() const;
    private:
        uint8_t mipmapLevel_;
    };

    class CommanderGetJobArtifactRequest : public ACommanderJobRequest
    {
    public:
        CommanderGetJobArtifactRequest(uint32_t jobId);

        SerializedParcel serialize(AParcelSerializer& serializer) const override;
        ParcelHandle dispatch(ACommanderRequestParcelDispatcher& dispatcher) const override;
    };

    class CommanderSetJobStateRequest : public ACommanderJobRequest
    {
    public:
        CommanderSetJobStateRequest(uint32_t jobId, JobState jobState);

        SerializedParcel serialize(AParcelSerializer& serializer) const override;
        ParcelHandle dispatch(ACommanderRequestParcelDispatcher& dispatcher) const override;

        JobState get_job_state() const;
    private:
        JobState jobState_;
    };

    class CommanderAddJobRequest : public ACommanderJobRequest
    {
    public:
        CommanderAddJobRequest(uint32_t jobId, uint32_t scene_id, float scale);

        SerializedParcel serialize(AParcelSerializer& serializer) const override;
        ParcelHandle dispatch(ACommanderRequestParcelDispatcher& dispatcher) const override;

        uint32_t get_scene_id() const;
        float get_scale() const;

    private:
        uint32_t sceneId_;
        float scale_;
    };

    class CommanderGetSceneListRequest : public ACommanderRequestParcel
    {
    public:
        SerializedParcel serialize(AParcelSerializer& serializer) const override;
        ParcelHandle dispatch(ACommanderRequestParcelDispatcher& dispatcher) const override;
    };

    class CommanderGetNodeListRequest : public ACommanderRequestParcel
    {
    public:
        SerializedParcel serialize(AParcelSerializer& serializer) const override;
        ParcelHandle dispatch(ACommanderRequestParcelDispatcher& dispatcher) const override;
    };

    class ACommanderNodeRequest : public ACommanderRequestParcel
    {
    public:
        ACommanderNodeRequest(uint32_t nodeId);

        uint32_t get_node_id() const;

    private:
        uint32_t nodeId_;
    };

    class CommanderGetNodeInfoRequest : public ACommanderNodeRequest
    {
    public:
        CommanderGetNodeInfoRequest(uint32_t jobId);

        SerializedParcel serialize(AParcelSerializer& serializer) const override;
        ParcelHandle dispatch(ACommanderRequestParcelDispatcher& dispatcher) const override;
    };

    class CommanderSetNodeStateRequest : public ACommanderNodeRequest
    {
    public:
        CommanderSetNodeStateRequest(uint32_t jobId, NodeState nodeState);

        SerializedParcel serialize(AParcelSerializer& serializer) const override;
        ParcelHandle dispatch(ACommanderRequestParcelDispatcher& dispatcher) const override;

        NodeState get_node_state() const;

    private:
        NodeState nodeState_;
    };
}