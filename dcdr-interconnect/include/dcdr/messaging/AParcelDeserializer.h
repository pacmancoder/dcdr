#pragma once

#include <vector>
#include <cstdint>

#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{

    class AParcelDeserializer
    {
    public:
        using SerializedParcel = std::vector<uint8_t>;

    public:
        virtual IParcel::ParcelPtr deserialize(IParcel::SerializedParcel serializedParcel) = 0;

        ~AParcelDeserializer() = default;

    protected:
        IParcel::ParcelPtr deserialize_not_supported();

    };
}