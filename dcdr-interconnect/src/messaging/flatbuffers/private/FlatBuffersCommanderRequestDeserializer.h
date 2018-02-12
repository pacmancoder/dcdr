#pragma once

#include <dcdr/messaging/IParcel.h>
#include <flatbuffers-generated/DcdrFlatBuffers.h>

namespace Dcdr::Interconnect::FlatBuffers
{
    class FlatBuffersCommanderRequestDeserializer
    {
    public:
        IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderRequest* request) const;
    };
}