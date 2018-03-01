#include "FlatBuffersWorkerResponseDeserializer.h"

#include <dcdr/messaging/InterconnectExceptions.h>
#include <dcdr/messaging/worker/WorkerResponseParcels.h>

#include "FlatBuffersDeserializerUtils.h"

using namespace Dcdr::Interconnect;
using namespace Dcdr::Interconnect::FlatBuffers;

namespace
{
    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerLoginResponse* request)
    {
        return std::make_unique<WorkerLoginResponseParcel>(
                request->nodeId());
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerServerStatusResponse* request)
    {
        return std::make_unique<WorkerServerStatusResponseParcel>(
                request->nodeId(),
                DeserializerUtils::marshal(request->status()),
                request->message()->str());
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerPollTasksResponse* request)
    {
        return std::make_unique<WorkerPollTasksResponseParcel>(
                request->nodeId(),
                DeserializerUtils::deserialize_vector<DcdrFlatBuffers::TaskInfo, Worker::TaskInfo>(
                        request->taskList()));
    }

    IParcel::ParcelPtr deserialize(const DcdrFlatBuffers::WorkerDownloadSceneResponse* request)
    {
        return std::make_unique<WorkerDownloadSceneResponseParcel>(
                request->nodeId(),
                request->sceneId(),
                request->offset(),
                request->bytesLeft(),
                std::vector<uint8_t>(request->data()->begin(), request->data()->end()));
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
    }

    throw DeserializationNotImplementedException("<Unknown>");
}
