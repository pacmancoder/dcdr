#include <dcdr/messaging/worker/AWorkerRequestParcel.h>

#include <dcdr/messaging/IParcelDispatcher.h>
#include <dcdr/messaging/IParcelSerializer.h>

using namespace Dcdr::Interconnect;

IParcel::ParcelPtr AWorkerRequestParcel::dispatch(IParcelDispatcher &dispatcher) const
{
    return dispatcher.dispatch(*this);
}

IParcel::SerializedParcel AWorkerRequestParcel::serialize(IParcelSerializer &serializer) const
{
    return serializer.serialize(*this);
}
