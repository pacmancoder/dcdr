#include "FlatBuffersWorkerResponseDeserializer.h"

#include <dcdr/messaging/InterconnectExceptions.h>
#include <dcdr/messaging/worker/WorkerResponseParcels.h>

#include "FlatBuffersDeserializerUtils.h"

using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

namespace
{
    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerLoginResponse* response)
    {
        return std::make_unique<WorkerLoginResponseParcel>(
                response->nodeId());
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerServerStatusResponse* response)
    {
        return std::make_unique<WorkerServerStatusResponseParcel>(
                response->nodeId(),
                DeserializerUtils::marshal(response->status()),
                response->message()->str());
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerPollTasksResponse* response)
    {
        return std::make_unique<WorkerPollTasksResponseParcel>(
                response->nodeId(),
                DeserializerUtils::deserialize_vector<DcdrFlatBuffers::TaskInfo, Worker::TaskInfo>(
                        response->taskList()));
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerDownloadSceneResponse* response)
    {
        return std::make_unique<WorkerDownloadSceneResponseParcel>(
                response->nodeId(),
                response->sceneId(),
                response->offset(),
                response->bytesLeft(),
                std::vector<uint8_t>(response->data()->begin(), response->data()->end()));
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerGetSceneInfoResponse* response)
    {
        return std::make_unique<WorkerGetSceneInfoResponseParcel>(
                response->nodeId(),
                response->sceneId(),

                response->width(),
                response->height(),

                response->fileName()->str());
    }
}

IParcel::ParcelPtr
FlatBuffersWorkerResponseDeserializer::deserialize(const DcdrFlatBuffers::WorkerResponse *response) const
{
    switch (response->responseData_type())
    {
        case DcdrFlatBuffers::WorkerResponseData_NONE:
            return nullptr;
        case DcdrFlatBuffers::WorkerResponseData_WorkerServerStatusResponse:
            return ::deserialize(response->responseData_as_WorkerServerStatusResponse());
        case DcdrFlatBuffers::WorkerResponseData_WorkerLoginResponse:
            return ::deserialize(response->responseData_as_WorkerLoginResponse());
        case DcdrFlatBuffers::WorkerResponseData_WorkerPollTasksResponse:
            return ::deserialize(response->responseData_as_WorkerPollTasksResponse());
        case DcdrFlatBuffers::WorkerResponseData_WorkerDownloadSceneResponse:
            return ::deserialize(response->responseData_as_WorkerDownloadSceneResponse());
        case DcdrFlatBuffers::WorkerResponseData_WorkerGetSceneInfoResponse:
            return ::deserialize(response->responseData_as_WorkerGetSceneInfoResponse());
    }

    throw DeserializationNotImplementedException("<Unknown>");
}
