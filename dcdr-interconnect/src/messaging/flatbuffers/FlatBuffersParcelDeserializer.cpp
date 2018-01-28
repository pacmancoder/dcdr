#include <dcdr/messaging/flatbuffers/FlatBuffersParcelDeserializer.h>

#include <algorithm>
#include <serialization/FlatBuffers.h>
#include <dcdr/logging/Logger.h>
#include <dcdr/messaging/InterconnectExceptions.h>
#include <dcdr/messaging/worker/AWorkerRequestParcel.h>
#include <dcdr/messaging/worker/WorkerConnectRequest.h>
#include <dcdr/messaging/commander/ACommanderRequestParcel.h>
#include <dcdr/messaging/commander/ACommanderResponseParcel.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceRequest.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceResponse.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceInfoRequest.h>
#include <dcdr/messaging/commander/CommanderGetSurfaceInfoResponse.h>

using namespace Dcdr::Logging;
using namespace Dcdr::Interconnect;

namespace
{

    AWorkerRequestParcel::WorkerRequestParcelPtr deserialize_worker_connect_request(
            const DcdrFlatBuffers::WorkerConnectRequest* data)
    {
        auto parcel = std::make_unique<WorkerConnectRequest>();

        WorkerConnectRequest::Token token{};
        if (data->token()->size() != std::tuple_size<WorkerConnectRequest::Token>::value)
        {
            throw DeserializationException("Token field of ConnectRequest has wrong size");
        }
        std::copy(data->token()->begin(), data->token()->end(), token.begin());
        parcel->set_token(token);

        log_debug("[Interconnect][FlatBuffers] Parcel was deserialized to WorkerConnectRequest");
        return std::move(parcel);
    }

    ACommanderRequestParcel::CommanderRequestParcelPtr deserialize_commander_get_surface_info_request(
            const DcdrFlatBuffers::CommanderGetSurfaceInfoRequest*)
    {
        log_debug("[Interconnect][FlatBuffers] Parcel was deserialized to CommanderGetSurfaceInfoRequest");
        return std::make_unique<CommanderGetSurfaceInfoRequest>();
    }

    ACommanderRequestParcel::CommanderRequestParcelPtr deserialize_commander_get_surface_request(
            const DcdrFlatBuffers::CommanderGetSurfaceRequest*)
    {
        log_debug("[Interconnect][FlatBuffers] Parcel was deserialized to CommanderGetSurfaceRequest");
        return std::make_unique<CommanderGetSurfaceRequest>();
    }

    ACommanderResponseParcel::CommanderResponseParcelPtr deserialize_commander_get_surface_info_response(
            const DcdrFlatBuffers::CommanderGetSurfaceInfoResponse* getSurfaceInfoResponse)
    {
        auto parcel = std::make_unique<CommanderGetSurfaceInfoResponse>();

        parcel->set_width(getSurfaceInfoResponse->width());
        parcel->set_height(getSurfaceInfoResponse->height());

        log_debug("[Interconnect][FlatBuffers] Parcel was deserialized to CommanderGetSurfaceInfoResponse");
        return std::move(parcel);
    }

    ACommanderResponseParcel::CommanderResponseParcelPtr deserialize_commander_get_surface_response(
            const DcdrFlatBuffers::CommanderGetSurfaceResponse* getSurfaceResponse)
    {
        auto parcel = std::make_unique<CommanderGetSurfaceResponse>();
        parcel->set_image(
                static_cast<CommanderGetSurfaceResponse::ImageFormat>(getSurfaceResponse->format()),
                CommanderGetSurfaceResponse::ImageBuffer(
                        getSurfaceResponse->buffer()->begin(), getSurfaceResponse->buffer()->end()));

        log_debug("[Interconnect][FlatBuffers] Parcel was deserialized to CommanderGetSurfaceResponse");
        return std::move(parcel);
    }

    AWorkerRequestParcel::WorkerRequestParcelPtr deserialize_worker_request(
            const DcdrFlatBuffers::WorkerRequest* workerRequest)
    {

        AWorkerRequestParcel::WorkerRequestParcelPtr parcel = nullptr;

        switch (workerRequest->requestData_type())
        {
            case DcdrFlatBuffers::WorkerRequestData_WorkerConnectRequest:
            {
                parcel = deserialize_worker_connect_request(workerRequest->requestData_as_WorkerConnectRequest());
                break;
            }
            default:
            {
                parcel = nullptr;
            }
        }
        // obtain common fields for all worker requests
        if (parcel != nullptr)
        {
            AWorkerRequestParcel::SessionID sessionID{};
            if (workerRequest->session()->size() != std::tuple_size<AWorkerRequestParcel::SessionID>::value)
            {
                throw DeserializationException("SessionID field has wrong size");
            }
            std::copy(workerRequest->session()->begin(), workerRequest->session()->end(), sessionID.begin());
            parcel->set_session_id(sessionID);
        }

        log_debug("[Interconnect][FlatBuffers] Parcel was deserialized to WorkerConnectRequest");
        return std::move(parcel);
    };

    ACommanderRequestParcel::CommanderRequestParcelPtr deserialize_commander_request(
            const DcdrFlatBuffers::CommanderRequest* commanderRequest)
    {
        switch (commanderRequest->requestData_type())
        {
            case DcdrFlatBuffers::CommanderRequestData_CommanderGetSurfaceInfoRequest:
            {
                return deserialize_commander_get_surface_info_request(
                        commanderRequest->requestData_as_CommanderGetSurfaceInfoRequest());
            }
            case DcdrFlatBuffers::CommanderRequestData_CommanderGetSurfaceRequest:
            {
                return deserialize_commander_get_surface_request(
                        commanderRequest->requestData_as_CommanderGetSurfaceRequest());
            }
            default:
            {
                return nullptr;
            }
        }
    };

    ACommanderResponseParcel::CommanderResponseParcelPtr deserialize_commander_response(
            const DcdrFlatBuffers::CommanderResponse* commanderResponse)
    {
        switch (commanderResponse->responseData_type())
        {
            case DcdrFlatBuffers::CommanderResponseData_CommanderGetSurfaceInfoResponse:
            {
                return deserialize_commander_get_surface_info_response(
                        commanderResponse->responseData_as_CommanderGetSurfaceInfoResponse());
            }
            case DcdrFlatBuffers::CommanderResponseData_CommanderGetSurfaceResponse:
            {
                return deserialize_commander_get_surface_response(
                        commanderResponse->responseData_as_CommanderGetSurfaceResponse());
            }
            default:
            {
                return nullptr;
            }
        }
    };
}

#include <iostream>

IParcel::ParcelPtr FlatBuffersParcelDeserializer::deserialize(IParcel::SerializedParcel serializedParcel)
{
    auto requestFlatBuffer = flatbuffers::GetRoot<DcdrFlatBuffers::Parcel>(serializedParcel.data());

    switch (requestFlatBuffer->parcelData_type())
    {
        case DcdrFlatBuffers::ParcelData_WorkerRequest:
        {
            return deserialize_worker_request(requestFlatBuffer->parcelData_as_WorkerRequest());
        }
        case DcdrFlatBuffers::ParcelData_CommanderRequest:
        {
            return deserialize_commander_request(requestFlatBuffer->parcelData_as_CommanderRequest());
        }
        case DcdrFlatBuffers::ParcelData_CommanderResponse:
        {
            return deserialize_commander_response(requestFlatBuffer->parcelData_as_CommanderResponse());
        }
        default:
        {
            log_warning(std::string("[Interconnect][Flatbuffers] Frame with type ").append(std::to_string(requestFlatBuffer->parcelData_type())).append(" not supported"));
            return deserialize_not_supported();
        }
    }
}