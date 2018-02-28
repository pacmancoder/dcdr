#pragma once

#include <cstdint>
#include <memory>

#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{
    class IWorkerResponseDispatcher;
    class IWorkerResponseSerializer;

    class AWorkerResponseParcel : public IParcel
    {
    public:
        using WorkerRequestParcelPtr = std::unique_ptr<AWorkerResponseParcel>;

    public:
        IParcel::ParcelPtr dispatch(IParcelDispatcher& dispatcher) const override;
        IParcel::SerializedParcel serialize(IParcelSerializer& serializer) const override;

        virtual IParcel::ParcelPtr dispatch(IWorkerResponseDispatcher& dispatcher) const = 0;
        virtual IParcel::SerializedParcel serialize(IWorkerResponseSerializer& serializer) const = 0;
    };
}