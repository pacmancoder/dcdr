#pragma once

#include <dcdr/messaging/AParcelSerializer.h>
#include <memory>

namespace Dcdr::Interconnect
{

    class FlatBuffersParcelSerializer : public AParcelSerializer
    {
    public:
        IParcel::SerializedParcel serialize(const CommanderGetJobListRequest& parcel) override;

        IParcel::SerializedParcel serialize(const CommanderGetJobInfoRequest& parcel) override;

        IParcel::SerializedParcel serialize(const CommanderGetJobPreviewRequest& parcel) override;

        IParcel::SerializedParcel serialize(const CommanderGetJobArtifactRequest& parcel) override;

        IParcel::SerializedParcel serialize(const CommanderSetJobStateRequest& parcel) override;

        IParcel::SerializedParcel serialize(const CommanderAddJobRequest& parcel) override;

        IParcel::SerializedParcel serialize(const CommanderGetSceneListRequest& parcel) override;

        IParcel::SerializedParcel serialize(const CommanderGetNodeListRequest& parcel) override;

        IParcel::SerializedParcel serialize(const CommanderGetNodeInfoRequest& parcel) override;

        IParcel::SerializedParcel serialize(const CommanderSetNodeStateRequest& parcel) override;

        IParcel::SerializedParcel serialize(const CommanderGetSurfaceInfoResponse& parcel) override;

        IParcel::SerializedParcel serialize(const CommanderGetSurfaceResponse& parcel) override;

    public:
        //IParcel::SerializedParcel serialize(const WorkerConnectRequest& parcel) override;

        //IParcel::SerializedParcel serialize(const CommanderGetSurfaceInfoRequest& parcel) override;
        //IParcel::SerializedParcel serialize(const CommanderGetSurfaceRequest& parcel) override;

        //IParcel::SerializedParcel serialize(const CommanderGetSurfaceInfoResponse& parcel) override;
        //IParcel::SerializedParcel serialize(const CommanderGetSurfaceResponse& parcel) override;
    };
}