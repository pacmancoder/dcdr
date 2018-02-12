#include "FlatBuffersCommanderResponseDeserializer.h"

#include <dcdr/messaging/InterconnectExceptions.h>
#include <dcdr/messaging/commander/CommanderResponseParcels.h>

#include "FlatBuffersDeserializerUtils.h"

using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

namespace
{
    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderGetJobListResponse* response)
    {
        return std::make_unique<CommanderGetJobListResponseParcel>(
                DeserializerUtils::deserialize_vector<DcdrFlatBuffers::Job, Commander::Job>(response->jobs()));
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderGetJobInfoResponse* response)
    {
        return std::make_unique<CommanderGetJobInfoResponseParcel>(
                response->id(),
                DeserializerUtils::deserialize_vector<DcdrFlatBuffers::PropertyPair, Commander::PropertyPair>(
                        response->properties()));
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderGetJobPreviewResponse* response)
    {
        return std::make_unique<CommanderGetJobPreviewResponseParcel>(
                response->id(),
                std::vector<uint8_t>(response->data()->begin(), response->data()->end()));
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderGetJobArtifactResponse* response)
    {
        return std::make_unique<CommanderGetJobArtifactResponseParcel>(
                response->id(),
                std::vector<uint8_t>(response->data()->begin(), response->data()->end()));
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderDoJobListUpdateResponse*)
    {
        return std::make_unique<CommanderDoJobListUpdateResponseParcel>();
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderGetNodeListResponse* response)
    {
        return std::make_unique<CommanderGetNodeListResponseParcel>(
                DeserializerUtils::deserialize_vector<DcdrFlatBuffers::Node, Commander::Node>(
                        response->nodes()));
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderGetNodeInfoResponse* response)
    {
        return std::make_unique<CommanderGetNodeInfoResponseParcel>(
                response->id(),
                DeserializerUtils::deserialize_vector<DcdrFlatBuffers::PropertyPair, Commander::PropertyPair>(
                        response->properties()));
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderDoNodeListUpdateResponse*)
    {
        return std::make_unique<CommanderDoNodeListUpdateResponseParcel>();
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderDoShowErrorResponse* response)
    {
        return std::make_unique<CommanderDoShowErrorResponseParcel>(
                DeserializerUtils::marshal(response->error()),
                response->message()->str());
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderGetSceneListReponse* response)
    {
        return std::make_unique<CommanderGetSceneListReponseParcel>(
                DeserializerUtils::deserialize_vector<DcdrFlatBuffers::Scene, Commander::Scene>(response->scenes()));
    }
}

using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

IParcel::ParcelPtr FlatBuffersCommanderResponseDeserializer::deserialize(
        const DcdrFlatBuffers::CommanderResponse* response) const
{
    switch (response->responseData_type())
    {
        case DcdrFlatBuffers::CommanderResponseData_NONE:
            return nullptr;
        case DcdrFlatBuffers::CommanderResponseData_CommanderGetJobListResponse:
            return  ::deserialize(response->responseData_as_CommanderGetJobListResponse());
        case DcdrFlatBuffers::CommanderResponseData_CommanderGetJobInfoResponse:
            return  ::deserialize(response->responseData_as_CommanderGetJobInfoResponse());
        case DcdrFlatBuffers::CommanderResponseData_CommanderGetJobPreviewResponse:
            return  ::deserialize(response->responseData_as_CommanderGetJobPreviewResponse());
        case DcdrFlatBuffers::CommanderResponseData_CommanderGetJobArtifactResponse:
            return  ::deserialize(response->responseData_as_CommanderGetJobArtifactResponse());
        case DcdrFlatBuffers::CommanderResponseData_CommanderDoJobListUpdateResponse:
            return  ::deserialize(response->responseData_as_CommanderDoJobListUpdateResponse());
        case DcdrFlatBuffers::CommanderResponseData_CommanderGetNodeListResponse:
            return  ::deserialize(response->responseData_as_CommanderGetNodeListResponse());
        case DcdrFlatBuffers::CommanderResponseData_CommanderGetNodeInfoResponse:
            return  ::deserialize(response->responseData_as_CommanderGetNodeInfoResponse());
        case DcdrFlatBuffers::CommanderResponseData_CommanderDoNodeListUpdateResponse:
            return  ::deserialize(response->responseData_as_CommanderDoNodeListUpdateResponse());
        case DcdrFlatBuffers::CommanderResponseData_CommanderDoShowErrorResponse:
            return  ::deserialize(response->responseData_as_CommanderDoShowErrorResponse());
        case DcdrFlatBuffers::CommanderResponseData_CommanderGetSceneListReponse:
            return  ::deserialize(response->responseData_as_CommanderGetSceneListReponse());
    }

    throw DeserializationNotImplementedException("<Unknown>");
}
