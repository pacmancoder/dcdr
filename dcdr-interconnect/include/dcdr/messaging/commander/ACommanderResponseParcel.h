#pragma once

#include <dcdr/messaging/IParcel.h>
#include <memory>

namespace Dcdr::Interconnect
{
    class ICommanderResponseDispatcher;
    class ICommanderResponseSerializer;

    class ACommanderResponseParcel : public IParcel
    {
    public:
        using CommanderResponseParcelPtr = std::unique_ptr<ACommanderResponseParcel>;

    public:
        IParcel::ParcelPtr dispatch(IParcelDispatcher& dispatcher) const override;
        SerializedParcel serialize(IParcelSerializer& serializer) const override;

        virtual void dispatch(ICommanderResponseDispatcher& dispatcher) const = 0;
        virtual SerializedParcel serialize(ICommanderResponseSerializer& serializer) const = 0;
    };
}