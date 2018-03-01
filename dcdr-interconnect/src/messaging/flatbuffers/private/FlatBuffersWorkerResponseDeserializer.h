#pragma once

#include <dcdr/messaging/IParcel.h>
#include <flatbuffers-generated/DcdrFlatBuffers.h>

namespace Dcdr::Interconnect::FlatBuffers
{
    class FlatBuffersWorkerResponseDeserializer
    {
    public:
        IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerResponse* response) const;

    };
}