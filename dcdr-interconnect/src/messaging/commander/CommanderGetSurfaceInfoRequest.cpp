#include <dcdr/messaging/commander/CommanderGetSurfaceInfoRequest.h>
#include <dcdr/messaging/AParcelSerializer.h>

using namespace Dcdr::Interconnect;

IParcel::SerializedParcel CommanderGetSurfaceInfoRequest::serialize(AParcelSerializer& serializer)
{
    return serializer.serialize(*this);
}
