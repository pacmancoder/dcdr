#pragma once

#include <dcdr/messaging/IParcelSerializer.h>
#include <memory>

namespace Dcdr::Interconnect
{
    class FlatBuffersParcelSerializer : public IParcelSerializer
    {
    public:
        FlatBuffersParcelSerializer();

        IParcel::SerializedParcel serialize(const ACommanderRequestParcel& parcel) override;

        IParcel::SerializedParcel serialize(const ACommanderResponseParcel& parcel) override;

        virtual ~FlatBuffersParcelSerializer();

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}