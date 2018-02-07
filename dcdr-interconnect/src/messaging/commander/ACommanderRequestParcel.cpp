#include <dcdr/messaging/commander/ACommanderRequestParcel.h>

#include <dcdr/messaging/IParcelDispatcher.h>
#include <dcdr/messaging/IParcelSerializer.h>

using namespace Dcdr::Interconnect;

IParcel::ParcelHandle ACommanderRequestParcel::dispatch(IParcelDispatcher& dispatcher) const
{
    return dispatcher.dispatch(*this);
}

IParcel::SerializedParcel ACommanderRequestParcel::serialize(IParcelSerializer& serializer) const
{
    return serializer.serialize(*this);
}
