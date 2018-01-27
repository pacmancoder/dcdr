#pragma once

#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{
    class ACommanderRequestParcel : public IParcel
    {
    public:
        using CommanderRequestParcelPtr = std::unique_ptr<ACommanderRequestParcel>;

    public:
        ParcelHandle dispatch(AParcelDispatcher& dispatcher) override;

    };
}