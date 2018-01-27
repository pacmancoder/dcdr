#pragma once

#include <dcdr/messaging/IParcel.h>
#include <memory>

namespace Dcdr::Interconnect
{
    class ACommanderResponseParcel : public IParcel
    {
    public:
        using CommanderResponseParcelPtr = std::unique_ptr<ACommanderResponseParcel>;

    public:
        ParcelHandle dispatch(AParcelDispatcher& dispatcher) override;

    };
}