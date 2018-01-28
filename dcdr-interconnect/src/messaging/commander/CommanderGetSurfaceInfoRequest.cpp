#include <dcdr/messaging/commander/CommanderGetSurfaceInfoRequest.h>
#include <dcdr/messaging/commander/ACommanderRequestParcelDispatcher.h>
#include <dcdr/messaging/AParcelSerializer.h>

using namespace Dcdr::Interconnect;

IParcel::SerializedParcel CommanderGetSurfaceInfoRequest::serialize(AParcelSerializer& serializer) const
{
    return serializer.serialize(*this);
}

IParcel::ParcelHandle CommanderGetSurfaceInfoRequest::dispatch(ACommanderRequestParcelDispatcher& dispatcher) const
{
    return dispatcher.dispatch(*this);
}
