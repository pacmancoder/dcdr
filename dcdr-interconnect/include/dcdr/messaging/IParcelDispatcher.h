#pragma once

#include <future>
#include <string>
#include <dcdr/messaging/IParcel.h>
#include <dcdr/messaging/InterconnectExceptions.h>

namespace Dcdr::Interconnect
{
    class ACommanderRequestParcel;
    class ACommanderResponseParcel;
    class AWorkerRequestParcel;
    class AWorkerResponseParcel;

    class IParcelDispatcher
    {
    public:
        virtual IParcel::ParcelPtr dispatch(const ACommanderRequestParcel&)
        {
            dispatch_not_implemented("ACommanderRequestParcel");
            return nullptr;
        };
        virtual void dispatch(const ACommanderResponseParcel&)
        {
            dispatch_not_implemented("ACommanderResponseParcel");
        };

        virtual IParcel::ParcelPtr dispatch(const AWorkerRequestParcel&)
        {
            dispatch_not_implemented("AWorkerRequestParcel");
            return nullptr;
        }

        virtual void dispatch(const AWorkerResponseParcel&)
        {
            dispatch_not_implemented("AWorkerResponseParcel");
        }

        virtual void dispatch_not_implemented(const std::string& parcelKind)
        {
            throw DispatchNotImplemented(std::string("Dispatch not implemented for ").append(parcelKind));
        };


        virtual ~IParcelDispatcher() = default;
    };
}