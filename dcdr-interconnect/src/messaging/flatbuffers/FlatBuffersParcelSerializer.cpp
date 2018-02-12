#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>
#include <dcdr/messaging/commander/ACommanderRequestParcel.h>
#include <dcdr/messaging/commander/ACommanderResponseParcel.h>
#include <dcdr/messaging/InterconnectExceptions.h>

#include "private/FlatBuffersCommanderRequestSerializer.h"
#include "private/FlatBuffersCommanderResponseSerializer.h"

using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

IParcel::SerializedParcel FlatBuffersParcelSerializer::serialize(const ACommanderRequestParcel& parcel)
{
    FlatBuffersCommanderRequestSerializer serializer;
    return parcel.serialize(serializer);
}

IParcel::SerializedParcel FlatBuffersParcelSerializer::serialize(const ACommanderResponseParcel& parcel)
{
    FlatBuffersCommanderResponseSerializer serializer;
    return parcel.serialize(serializer);
}
