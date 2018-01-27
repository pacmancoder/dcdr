#include <dcdr/messaging/commander/CommanderGetSurfaceRequest.h>
#include <dcdr/messaging/AParcelSerializer.h>

using namespace Dcdr::Interconnect;

IParcel::SerializedParcel CommanderGetSurfaceRequest::serialize(AParcelSerializer& serializer)
{
    return serializer.serialize(*this);
}
