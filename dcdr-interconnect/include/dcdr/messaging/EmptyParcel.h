#pragma once

#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{
    class EmptyParcel : public IParcel
    {
    public:
        virtual ParcelHandle dispatch(IParcelDispatcher& dispatcher) override;
    };
}