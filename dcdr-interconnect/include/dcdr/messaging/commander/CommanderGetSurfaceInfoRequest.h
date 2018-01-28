#pragma once

#include <cstdint>
#include <dcdr/messaging/commander/ACommanderRequestParcel.h>

namespace Dcdr::Interconnect
{
    class CommanderGetSurfaceInfoRequest : public ACommanderRequestParcel
    {
    public:
        SerializedParcel serialize(AParcelSerializer& serializer) const override;

        ParcelHandle dispatch(ACommanderRequestParcelDispatcher& dispatcher) const override;
    };
}