#pragma once

#include <memory>
#include <future>
#include <vector>
#include <cstdint>

namespace Dcdr::Interconnect
{
    class AParcelDispatcher;
    class AParcelSerializer;

    class IParcel
    {
    public:
        using ParcelPtr = std::unique_ptr<IParcel>;
        using ParcelHandle = std::future<std::unique_ptr<IParcel>>;
        using SerializedParcel = std::vector<uint8_t>;

    public:
        virtual ParcelHandle dispatch(AParcelDispatcher& dispatcher) const = 0;
        virtual SerializedParcel serialize(AParcelSerializer& serializer) const = 0;

        virtual ~IParcel() = default;
    };
}