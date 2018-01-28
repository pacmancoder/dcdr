#include <dcdr/messaging/commander/CommanderGetSurfaceRequest.h>
#include <dcdr/messaging/commander/ACommanderRequestParcelDispatcher.h>
#include <dcdr/messaging/AParcelSerializer.h>

using namespace Dcdr::Interconnect;

IParcel::SerializedParcel CommanderGetSurfaceRequest::serialize(AParcelSerializer& serializer) const
{
    return serializer.serialize(*this);
}

IParcel::ParcelHandle CommanderGetSurfaceRequest::dispatch(ACommanderRequestParcelDispatcher& dispatcher) const
{
    return dispatcher.dispatch(*this);
}
