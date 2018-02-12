#include "FlatBuffersCommanderRequestDeserializer.h"
#include <dcdr/messaging/commander/CommanderRequestParcels.h>
#include <dcdr/messaging/InterconnectExceptions.h>

#include "FlatBuffersDeserializerUtils.h"

using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

namespace
{
    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderGetJobListRequest*)
    {
        return std::make_unique<CommanderGetJobListRequestParcel>();
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderGetJobInfoRequest* request)
    {
        return std::make_unique<CommanderGetJobInfoRequestParcel>(request->jobId());
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderGetJobPreviewRequest* request)
    {
        return std::make_unique<CommanderGetJobPreviewRequestParcel>(request->jobId(), request->mipmapLevel());
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderGetJobArtifactRequest* request)
    {
        return std::make_unique<CommanderGetJobArtifactRequestParcel>(request->jobId());
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderSetJobStateRequest* request)
    {
        return std::make_unique<CommanderSetJobStateRequestParcel>(
                request->jobId(),
                DeserializerUtils::marshal(request->state()));
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderAddJobRequest* request)
    {
        return std::make_unique<CommanderAddJobRequestParcel>(
                request->sceneId(),
                request->scale());
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderGetSceneListRequest*)
    {
        return std::make_unique<CommanderGetSceneListRequestParcel>();
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderGetNodeListRequest*)
    {
        return std::make_unique<CommanderGetNodeListRequestParcel>();
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderGetNodeInfoRequest* request)
    {
        return std::make_unique<CommanderGetNodeInfoRequestParcel>(request->nodeId());
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::CommanderSetNodeStateRequest* request)
    {
        return std::make_unique<CommanderSetNodeStateRequestParcel>(
                request->nodeId(),
                DeserializerUtils::marshal(request->state())
        );
    }
}

IParcel::ParcelPtr FlatBuffersCommanderRequestDeserializer::deserialize(
        const DcdrFlatBuffers::CommanderRequest* request) const
{
    switch (request->requestData_type())
    {
        case DcdrFlatBuffers::CommanderRequestData_NONE:
            return nullptr;
        case DcdrFlatBuffers::CommanderRequestData_CommanderGetJobListRequest:
            return ::deserialize(request->requestData_as_CommanderGetJobListRequest());
        case DcdrFlatBuffers::CommanderRequestData_CommanderGetJobInfoRequest:
            return ::deserialize(request->requestData_as_CommanderGetJobInfoRequest());
        case DcdrFlatBuffers::CommanderRequestData_CommanderGetJobPreviewRequest:
            return ::deserialize(request->requestData_as_CommanderGetJobPreviewRequest());
        case DcdrFlatBuffers::CommanderRequestData_CommanderGetJobArtifactRequest:
            return ::deserialize(request->requestData_as_CommanderGetJobArtifactRequest());
        case DcdrFlatBuffers::CommanderRequestData_CommanderSetJobStateRequest:
            return ::deserialize(request->requestData_as_CommanderSetJobStateRequest());
        case DcdrFlatBuffers::CommanderRequestData_CommanderAddJobRequest:
            return ::deserialize(request->requestData_as_CommanderAddJobRequest());
        case DcdrFlatBuffers::CommanderRequestData_CommanderGetSceneListRequest:
            return ::deserialize(request->requestData_as_CommanderGetSceneListRequest());
        case DcdrFlatBuffers::CommanderRequestData_CommanderGetNodeListRequest:
            return ::deserialize(request->requestData_as_CommanderGetNodeListRequest());
        case DcdrFlatBuffers::CommanderRequestData_CommanderGetNodeInfoRequest:
            return ::deserialize(request->requestData_as_CommanderGetNodeInfoRequest());
        case DcdrFlatBuffers::CommanderRequestData_CommanderSetNodeStateRequest:
            return ::deserialize(request->requestData_as_CommanderSetNodeStateRequest());
    }

    throw DeserializationNotImplementedException("<Unknown>");
}
