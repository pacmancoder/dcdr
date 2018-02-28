#pragma once

#include <dcdr/messaging/IParcelSerializer.h>
#include <memory>

namespace Dcdr::Interconnect
{
    class FlatBuffersParcelSerializer : public IParcelSerializer
    {
    public:
        IParcel::SerializedParcel serialize(const ACommanderRequestParcel& parcel) override;
        IParcel::SerializedParcel serialize(const ACommanderResponseParcel& parcel) override;
        IParcel::SerializedParcel serialize(const AWorkerRequestParcel &parcel) override;
        IParcel::SerializedParcel serialize(const AWorkerResponseParcel &parcel) override;
    };
}