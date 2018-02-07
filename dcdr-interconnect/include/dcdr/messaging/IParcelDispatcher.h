#pragma once

#include <future>
#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{
    class ACommanderRequestParcel;
    class ACommanderResponseParcel;

    class IParcelDispatcher
    {
    public:
        virtual IParcel::ParcelHandle dispatch(const ACommanderRequestParcel& parcel);
        virtual IParcel::ParcelHandle dispatch(const ACommanderResponseParcel& parcel);

        virtual ~IParcelDispatcher() = default;
    };
}