#include <dcdr/messaging/worker/AWorkerResponseParcel.h>

#include <dcdr/messaging/IParcelSerializer.h>
#include <dcdr/messaging/IParcelDispatcher.h>

using namespace Dcdr::Interconnect;

IParcel::ParcelPtr AWorkerResponseParcel::dispatch(IParcelDispatcher &dispatcher) const
{
    dispatcher.dispatch(*this);
    return nullptr;
}

IParcel::SerializedParcel AWorkerResponseParcel::serialize(IParcelSerializer &serializer) const
{
    return serializer.serialize(*this);
}
