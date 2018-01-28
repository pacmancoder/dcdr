#pragma once

#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{
    class ACommanderRequestParcelDispatcher;

    class ACommanderRequestParcel : public IParcel
    {
    public:
        using CommanderRequestParcelPtr = std::unique_ptr<ACommanderRequestParcel>;

    public:
        ParcelHandle dispatch(AParcelDispatcher& dispatcher) const override;

        virtual ParcelHandle dispatch(ACommanderRequestParcelDispatcher& dispatcher) const = 0;

    };
}