#pragma once

#include <dcdr/messaging/IParcel.h>
#include <dcdr/messaging/commander/ICommanderRequestSerializer.h>
#include <memory>

namespace Dcdr::Interconnect
{

    class FlatBuffersCommanderRequestSerializer : public ICommanderRequestSerializer
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

    };
}