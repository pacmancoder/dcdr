#pragma once

#include <dcdr/messaging/commander/ACommanderRequestParcel.h>

namespace Dcdr::Interconnect
{
    class CommanderGetSurfaceRequest : public ACommanderRequestParcel
    {
    public:
        SerializedParcel serialize(AParcelSerializer& serializer) const override;

        ParcelHandle dispatch(ACommanderRequestParcelDispatcher& dispatcher) const override;
    };
}