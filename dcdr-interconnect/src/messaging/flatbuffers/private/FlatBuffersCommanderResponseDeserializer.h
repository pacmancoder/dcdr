#pragma once

#include <dcdr/messaging/IParcel.h>
#include <flatbuffers-generated/DcdrFlatBuffers.h>

namespace Dcdr::Interconnect::FlatBuffers
{
    class FlatBuffersCommanderResponseDeserializer
    {
    public:
        IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderResponse* response) const;
    };
}