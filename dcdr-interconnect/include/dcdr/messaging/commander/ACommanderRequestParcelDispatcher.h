#pragma once

#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{
    class CommanderGetSurfaceInfoRequest;
    class CommanderGetSurfaceRequest;

    class ACommanderRequestParcelDispatcher
    {
    public:
        virtual IParcel::ParcelHandle dispatch(const CommanderGetSurfaceInfoRequest& parcel);
        virtual IParcel::ParcelHandle dispatch(const CommanderGetSurfaceRequest& parcel);

        virtual ~ACommanderRequestParcelDispatcher() = default;

    protected:
        virtual IParcel::ParcelHandle dispatch_not_supported();

    private:

    };
}