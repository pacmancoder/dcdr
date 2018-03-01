#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>

#include <dcdr/messaging/commander/ACommanderRequestParcel.h>
#include <dcdr/messaging/commander/ACommanderResponseParcel.h>

#include <dcdr/messaging/worker/AWorkerRequestParcel.h>
#include <dcdr/messaging/worker/AWorkerResponseParcel.h>

#include <dcdr/messaging/InterconnectExceptions.h>

#include "private/FlatBuffersCommanderRequestSerializer.h"
#include "private/FlatBuffersCommanderResponseSerializer.h"

#include "private/FlatBuffersWorkerRequestSerializer.h"
#include "private/FlatBuffersWorkerResponseSerializer.h"

using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

namespace
{
    const size_t BATCH_PARCEL_BUILDER_BUFFER_SIZE = 4096;
}

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

IParcel::SerializedParcel FlatBuffersParcelSerializer::serialize(const AWorkerRequestParcel& parcel)
{
    FlatBuffersWorkerRequestSerializer serializer;
    return parcel.serialize(serializer);
}

IParcel::SerializedParcel FlatBuffersParcelSerializer::serialize(const AWorkerResponseParcel& parcel)
{
    FlatBuffersWorkerResponseSerizlizer serizlizer;
    return parcel.serialize(serizlizer);
}
