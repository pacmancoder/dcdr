#include <dcdr/messaging/flatbuffers/FlatBuffersParcelDeserializer.h>
#include <dcdr/messaging/InterconnectExceptions.h>

#include <flatbuffers-generated/DcdrFlatBuffers.h>

#include "private/FlatBuffersExceptions.h"
#include "private/FlatBuffersSerializerUtils.h"

#include "private/FlatBuffersCommanderRequestDeserializer.h"
#include "private/FlatBuffersCommanderResponseDeserializer.h"

#include "private/FlatBuffersWorkerRequestDeserializer.h"

using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

IParcel::ParcelPtr FlatBuffersParcelDeserializer::deserialize(IParcel::SerializedParcel serializedParcel)
{
    auto verifier = flatbuffers::Verifier(serializedParcel.data(), serializedParcel.size());

    if (!DcdrFlatBuffers::VerifyParcelBuffer(verifier))
    {
        throw FlatBuffersVerificationException();
    }

    auto parcelFlatBuffer = DcdrFlatBuffers::GetParcel(serializedParcel.data());

    switch (parcelFlatBuffer->parcelData_type())
    {
        case DcdrFlatBuffers::ParcelData_NONE:
            return nullptr;
        case DcdrFlatBuffers::ParcelData_WorkerRequest:
        {
            FlatBuffersWorkerRequestDeserializer deserializer;
            return deserializer.deserialize(parcelFlatBuffer->parcelData_as_WorkerRequest());
        }
        case DcdrFlatBuffers::ParcelData_WorkerResponse:
            throw DeserializationNotImplementedException("WorkerResponse");
        case DcdrFlatBuffers::ParcelData_CommanderRequest:
        {
            FlatBuffersCommanderRequestDeserializer deserializer;
            return deserializer.deserialize(parcelFlatBuffer->parcelData_as_CommanderRequest());
        }
        case DcdrFlatBuffers::ParcelData_CommanderResponse:
        {
            FlatBuffersCommanderResponseDeserializer deserializer;
            return deserializer.deserialize(parcelFlatBuffer->parcelData_as_CommanderResponse());
        }
    }

    throw DeserializationNotImplementedException("<Unknown>");
}