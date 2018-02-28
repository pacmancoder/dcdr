#pragma once

#include <cstdint>
#include <memory>

#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{
    class IWorkerRequestDispatcher;
    class IWorkerRequestSerializer;

    class AWorkerRequestParcel : IParcel
    {
    public:
        using WorkerRequestParcelPtr = std::unique_ptr<AWorkerRequestParcel>;

    public:
        IParcel::ParcelPtr dispatch(IParcelDispatcher& dispatcher) const override;
        SerializedParcel serialize(IParcelSerializer& serializer) const override;

        virtual ParcelPtr dispatch(IWorkerRequestDispatcher& dispatcher) const = 0;
        virtual SerializedParcel serialize(IWorkerRequestSerializer& serializer) const = 0;
    };
}