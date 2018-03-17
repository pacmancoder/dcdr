#include "FlatBuffersWorkerRequestDeserializer.h"

#include <dcdr/messaging/InterconnectExceptions.h>
#include <dcdr/messaging/worker/WorkerRequestParcels.h>

#include "FlatBuffersDeserializerUtils.h"

using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

namespace
{
    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerLoginRequest* request)
    {
        return std::make_unique<WorkerLoginRequestParcel>(
                request->name()->str(),
                request->token()->str());
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerLogoutRequest* request)
    {
        return std::make_unique<WorkerLogoutRequestParcel>(request->nodeId());
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerSendHardwareInfoRequest* request)
    {

        return std::make_unique<WorkerSendHardwareInfoRequestParcel>(
                request->nodeId(),
                DeserializerUtils::deserialize_vector<DcdrFlatBuffers::PropertyPair, PropertyPair>(
                        request->properties()));
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerPollTasksRequest* request)
    {
        return std::make_unique<WorkerPollTasksRequestParcel>(request->nodeId());
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerCommitTasksRequest* request)
    {

        return std::make_unique<WorkerCommitTasksRequestParcel>(
                request->nodeId(),
                DeserializerUtils::deserialize_vector<DcdrFlatBuffers::TaskArtifact, Worker::TaskArtifact>(
                        request->artifacts()));
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerDownloadSceneRequest* request)
    {
        return std::make_unique<WorkerDownloadSceneRequestParcel>(
                request->nodeId(), request->sceneId(), request->offset());
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerGetSceneInfoRequest* request)
    {
        return std::make_unique<WorkerGetSceneInfoRequestParcel>(
                request->nodeId(), request->sceneId());
    }
}


IParcel::ParcelPtr FlatBuffersWorkerRequestDeserializer::deserialize(
        const DcdrFlatBuffers::WorkerRequest* request) const
{
    switch (request->requestData_type())
    {
        case DcdrFlatBuffers::WorkerRequestData_NONE:
            return nullptr;
        case DcdrFlatBuffers::WorkerRequestData_WorkerLoginRequest:
            return ::deserialize(request->requestData_as_WorkerLoginRequest());
        case DcdrFlatBuffers::WorkerRequestData_WorkerLogoutRequest:
            return ::deserialize(request->requestData_as_WorkerLogoutRequest());
        case DcdrFlatBuffers::WorkerRequestData_WorkerSendHardwareInfoRequest:
            return ::deserialize(request->requestData_as_WorkerSendHardwareInfoRequest());
        case DcdrFlatBuffers::WorkerRequestData_WorkerPollTasksRequest:
            return ::deserialize(request->requestData_as_WorkerPollTasksRequest());
        case DcdrFlatBuffers::WorkerRequestData_WorkerCommitTasksRequest:
            return ::deserialize(request->requestData_as_WorkerCommitTasksRequest());
        case DcdrFlatBuffers::WorkerRequestData_WorkerDownloadSceneRequest:
            return ::deserialize(request->requestData_as_WorkerDownloadSceneRequest());
        case DcdrFlatBuffers::WorkerRequestData_WorkerGetSceneInfoRequest:
            return ::deserialize(request->requestData_as_WorkerGetSceneInfoRequest());
    }

    throw DeserializationNotImplementedException("<Unknown>");
}
