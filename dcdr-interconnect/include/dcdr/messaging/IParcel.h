#pragma once

#include <memory>
#include <future>
#include <vector>
#include <cstdint>

namespace Dcdr::Interconnect
{
    class IParcelDispatcher;
    class IParcelSerializer;

    class IParcel
    {
    public:
        using ParcelPtr = std::unique_ptr<IParcel>;
        using SerializedParcel = std::vector<uint8_t>;

    public:
        virtual ParcelPtr dispatch(IParcelDispatcher& dispatcher) const = 0;
        virtual ParcelPtr dispatch(IParcelDispatcher&& dispatcher) const
        {
            return dispatch(dispatcher);
        }

        virtual SerializedParcel serialize(IParcelSerializer& serializer) const = 0;
        virtual SerializedParcel serialize(IParcelSerializer&& serializer) const
        {
            return serialize(serializer);
        }

        virtual ~IParcel() = default;
    };
}