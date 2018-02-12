#include <dcdr/messaging/commander/ACommanderResponseParcel.h>
#include <dcdr/messaging/IParcelDispatcher.h>
#include <dcdr/messaging/IParcelSerializer.h>

using namespace Dcdr::Interconnect;

IParcel::ParcelHandle ACommanderResponseParcel::dispatch(IParcelDispatcher& dispatcher) const
{
    return dispatcher.dispatch(*this);
}

IParcel::SerializedParcel ACommanderResponseParcel::serialize(IParcelSerializer& serializer) const
{
    return serializer.serialize(*this);
}

