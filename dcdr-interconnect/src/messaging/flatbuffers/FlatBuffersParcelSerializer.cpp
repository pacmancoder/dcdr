#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersCommanderRequestSerializer.h>
#include <dcdr/messaging/commander/ACommanderRequestParcel.h>
#include <dcdr/messaging/InterconnectExceptions.h>

using namespace Dcdr::Interconnect;

struct FlatBuffersParcelSerializer::Impl
{
public:
    FlatBuffersCommanderRequestSerializer commanderRequestSerializer_;

    Impl() :
            commanderRequestSerializer_() {}
};


FlatBuffersParcelSerializer::FlatBuffersParcelSerializer() :
        impl_(new Impl()) {}

IParcel::SerializedParcel FlatBuffersParcelSerializer::serialize(const ACommanderRequestParcel& parcel)
{
    return parcel.serialize(impl_->commanderRequestSerializer_);
}

IParcel::SerializedParcel FlatBuffersParcelSerializer::serialize(const ACommanderResponseParcel&)
{
    throw SerializationNotImplementedException("ACommanderResponseParcel");
}

FlatBuffersParcelSerializer::~FlatBuffersParcelSerializer() = default;
