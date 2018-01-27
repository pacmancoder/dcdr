#pragma once

#include <future>
#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{

    class AWorkerRequestParcel;
    class ACommanderRequestParcel;
    class ACommanderResponseParcel;

    class AParcelDispatcher
    {
    public:
        virtual IParcel::ParcelHandle dispatch(const AWorkerRequestParcel& parcel);

        virtual IParcel::ParcelHandle dispatch(const ACommanderRequestParcel& parcel);
        virtual IParcel::ParcelHandle dispatch(const ACommanderResponseParcel& parcel);

        virtual ~AParcelDispatcher() = default;

    protected:
        virtual IParcel::ParcelHandle dispatch_not_supported();

    };
}