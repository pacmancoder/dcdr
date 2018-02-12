#pragma once

#include <dcdr/messaging/IParcel.h>
#include <dcdr/messaging/commander/ICommanderResponseSerializer.h>

namespace Dcdr::Interconnect::FlatBuffers
{
    class FlatBuffersCommanderResponseSerializer : public ICommanderResponseSerializer
    {
    public:
        IParcel::SerializedParcel serialize(const CommanderGetJobListResponse& parcel) override;
        IParcel::SerializedParcel serialize(const CommanderGetJobInfoResponse& parcel) override;
        IParcel::SerializedParcel serialize(const CommanderGetJobPreviewResponse& parcel) override;
        IParcel::SerializedParcel serialize(const CommanderGetJobArtifactResponse& parcel) override;
        IParcel::SerializedParcel serialize(const CommanderDoJobListUpdateResponse& parcel) override;
        IParcel::SerializedParcel serialize(const CommanderGetSceneListResponse& parcel) override;
        IParcel::SerializedParcel serialize(const CommanderGetNodeListResponse& parcel) override;
        IParcel::SerializedParcel serialize(const CommanderGetNodeInfoResponse& parcel) override;
        IParcel::SerializedParcel serialize(const CommanderDoNodeListUpdateResponse& parcel) override;
        IParcel::SerializedParcel serialize(const CommanderDoShowErrorResponse& parcel) override;
    };
}