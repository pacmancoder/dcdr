#pragma once

#include <future>
#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{

    class AWorkerRequestParcel;
    class ACommanderRequestParcel;

    class IParcelDispatcher
    {
    public:
        virtual IParcel::ParcelHandle dispatch(const AWorkerRequestParcel& parcel) = 0;
        virtual IParcel::ParcelHandle dispatch(const ACommanderRequestParcel& parcel) = 0;

        virtual ~IParcelDispatcher() = default;
    };
}