#pragma once

#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{

    class  ACommanderRequestParcel;
    class  ACommanderResponseParcel;

    /// @throws Dcdr::Interconnect::SerializationNotImplemented - if serialization is not implemented for parcel
    /// @throws Dcdr::Interconnect::SerializationFailed on underlying serializer error
    class IParcelSerializer
    {
    public:
        virtual IParcel::SerializedParcel serialize(const ACommanderRequestParcel&) = 0;
        virtual IParcel::SerializedParcel serialize(const ACommanderResponseParcel&) = 0;
        virtual ~IParcelSerializer() = default;
    };
}
