#pragma once

#include <dcdr/messaging/worker/IWorkerResponseSerializer.h>

namespace Dcdr::Interconnect::FlatBuffers
{
    class FlatBuffersWorkerResponseSerizlizer : public IWorkerResponseSerializer
    {
    public:
        IParcel::SerializedParcel serialize(const WorkerServerStatusResponse& parcel) override;
        IParcel::SerializedParcel serialize(const WorkerLoginResponse& parcel) override;
        IParcel::SerializedParcel serialize(const WorkerPollTasksResponse& parcel) override;
        IParcel::SerializedParcel serialize(const WorkerDownloadSceneResponse& parcel) override;
        IParcel::SerializedParcel serialize(const WorkerGetSceneInfoResponse& parcel) override;
    };
}