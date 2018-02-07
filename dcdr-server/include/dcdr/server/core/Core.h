#pragma once

#include <memory>
#include <dcdr/messaging/IParcelDispatcher.h>

namespace Dcdr::Server
{
    class Core : public Interconnect::IParcelDispatcher
    {
    public:
        Core();

        void run();

        Interconnect::IParcel::ParcelHandle dispatch(const Interconnect::ACommanderRequestParcel& parcel) override;
        Interconnect::IParcel::ParcelHandle dispatch(const Interconnect::ACommanderResponseParcel& parcel) override;
    };
}