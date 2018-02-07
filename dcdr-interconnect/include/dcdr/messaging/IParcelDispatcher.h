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
        virtual IParcel::ParcelHandle dispatch(const ACommanderRequestParcel& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const ACommanderResponseParcel& parcel) = 0;

        virtual ~IParcelDispatcher() = default;
    };
}