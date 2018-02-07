#pragma once

#include <dcdr/messaging/IParcelDeserializer.h>
#include <memory>

namespace Dcdr::Interconnect
{
    class ServerConnectionResolver;

    class FlatBuffersParcelDeserializer : public IParcelDeserializer
    {
    public:
        IParcel::ParcelPtr deserialize(IParcel::SerializedParcel serializedParcel) override;

    };
}