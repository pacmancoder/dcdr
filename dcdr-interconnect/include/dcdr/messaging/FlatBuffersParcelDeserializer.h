#pragma once

#include <dcdr/messaging/AParcelDeserializer.h>
#include <memory>

namespace Dcdr::Interconnect
{
    class ServerConnectionResolver;

    class FlatBuffersParcelDeserializer : public AParcelDeserializer
    {
    public:
        IParcel::ParcelPtr deserialize(IParcel::SerializedParcel& serializedParcel) override;

    };
}