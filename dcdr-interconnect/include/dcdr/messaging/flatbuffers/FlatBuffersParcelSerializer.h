#pragma once

#include <dcdr/messaging/AParcelSerializer.h>
#include <memory>

namespace Dcdr::Interconnect
{

    class FlatBuffersParcelSerializer : public AParcelSerializer
    {
    public:
        IParcel::SerializedParcel serialize(const WorkerConnectRequest& parcel) override;

        IParcel::SerializedParcel serialize(const CommanderGetSurfaceInfoRequest& parcel) override;
        IParcel::SerializedParcel serialize(const CommanderGetSurfaceRequest& parcel) override;

        IParcel::SerializedParcel serialize(const CommanderGetSurfaceInfoResponse& parcel) override;
        IParcel::SerializedParcel serialize(const CommanderGetSurfaceResponse& parcel) override;
    };
}