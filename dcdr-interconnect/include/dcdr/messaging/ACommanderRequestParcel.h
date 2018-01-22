#pragma once

#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{
    class ACommanderRequestParcel : public IParcel
    {
    public:
        ParcelHandle dispatch(IParcelDispatcher& dispatcher) override;

    };
}