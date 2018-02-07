#pragma once

#include <dcdr/messaging/IParcelDeserializer.h>
#include <memory>

namespace Dcdr::Interconnect
{
    class ServerConnectionResolver;

    class FlatBuffersParcelDeserializer : public IParcelDeserializer
    {
    public:
        /// Should return parcel or throw (uniqie ptr was used to not to store parcel on the stack)
        /// @throws Dcdr::Interconnect::DeserializationException
        IParcel::ParcelPtr deserialize(IParcel::SerializedParcel serializedParcel) override;
    };
}