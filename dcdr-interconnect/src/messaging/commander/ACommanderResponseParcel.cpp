#include <dcdr/messaging/commander/ACommanderResponseParcel.h>
#include <dcdr/messaging/IParcelDispatcher.h>
#include <dcdr/messaging/IParcelSerializer.h>

using namespace Dcdr::Interconnect;

IParcel::ParcelPtr ACommanderResponseParcel::dispatch(IParcelDispatcher& dispatcher) const
{
    dispatcher.dispatch(*this);
    return nullptr;
}

IParcel::SerializedParcel ACommanderResponseParcel::serialize(IParcelSerializer& serializer) const
{
    return serializer.serialize(*this);
}

