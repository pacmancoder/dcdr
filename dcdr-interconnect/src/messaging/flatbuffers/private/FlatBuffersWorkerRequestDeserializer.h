#pragma once

#include <dcdr/messaging/IParcel.h>
#include <flatbuffers-generated/DcdrFlatBuffers.h>

namespace Dcdr::Interconnect::FlatBuffers
{
    class FlatBuffersWorkerRequestDeserializer
    {
    public:
        IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerRequest* request) const;

    };
}