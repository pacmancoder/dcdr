#include <dcdr/messaging/FlatBuffersParcelDeserializer.h>

#include <algorithm>
#include <serialization/FlatBuffers.h>
#include <dcdr/messaging/AWorkerRequestParcel.h>
#include <dcdr/messaging/InterconnectExceptions.h>
#include <dcdr/messaging/WorkerConnectRequest.h>

using namespace Dcdr::Interconnect;

namespace
{

    AWorkerRequestParcel::WorkerRequestParcelPtr deserialize_connect_request(const DcdrFlatBuffers::ConnectRequestData* data)
    {
        auto parcel = std::make_unique<WorkerConnectRequest>();

        WorkerConnectRequest::Token token{};
        if (data->token()->size() != std::tuple_size<WorkerConnectRequest::Token>::value)
        {
            throw DeserializationException("Token field of ConnectRequest has wrong size");
        }
        std::copy(data->token()->begin(), data->token()->end(), token.begin());
        parcel->set_token(token);

        return std::move(parcel);
    }
}

IParcel::ParcelPtr FlatBuffersParcelDeserializer::deserialize(IParcel::SerializedParcel& serializedParcel)
{
    auto requestFlatBuffer = flatbuffers::GetRoot<DcdrFlatBuffers::WorkerRequest>(serializedParcel.data());

    AWorkerRequestParcel::WorkerRequestParcelPtr parcel = nullptr;

    switch (requestFlatBuffer->data_type())
    {
        case DcdrFlatBuffers::WorkerRequestData_ConnectRequestData:
        {
            parcel = deserialize_connect_request(requestFlatBuffer->data_as_ConnectRequestData());
            break;
        }
        default:
        {
            break;
        }
    }
    // obtain common fields for all worker requests
    if (parcel != nullptr)
    {
        AWorkerRequestParcel::SessionID sessionID{};
        if (requestFlatBuffer->session()->size() != std::tuple_size<AWorkerRequestParcel::SessionID>::value)
        {
            throw DeserializationException("SessionID field has wrong size");
        }
        std::copy(requestFlatBuffer->session()->begin(), requestFlatBuffer->session()->end(), sessionID.begin());
        parcel->set_session_id(sessionID);
    }

    return std::move(parcel);
}