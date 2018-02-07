#pragma once

#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{
    class ICommanderRequestDispatcher;
    class ICommanderRequestSerializer;

    class ACommanderRequestParcel : public IParcel
    {
    public:
        using CommanderRequestParcelPtr = std::unique_ptr<ACommanderRequestParcel>;

    public:
        IParcel::ParcelHandle dispatch(IParcelDispatcher& dispatcher) const override;
        SerializedParcel serialize(IParcelSerializer& serializer) const override;

        virtual ParcelHandle dispatch(ICommanderRequestDispatcher& dispatcher) const = 0;
        virtual SerializedParcel serialize(ICommanderRequestSerializer& serializer) const = 0;

    };
}