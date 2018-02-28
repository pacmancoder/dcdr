#pragma once

#include <dcdr/messaging/worker/IWorkerRequestSerializer.h>

namespace Dcdr::Interconnect::FlatBuffers
{
    class FlatBuffersWorkerRequestSerializer : public IWorkerRequestSerializer
    {
    public:
        IParcel::SerializedParcel serialize(const WorkerLoginRequest& parcel) override;
        IParcel::SerializedParcel serialize(const WorkerLogoutRequest& parcel) override;
        IParcel::SerializedParcel serialize(const WorkerSendHardwareInfoRequest& parcel) override;
        IParcel::SerializedParcel serialize(const WorkerPollTasksRequest& parcel) override;
        IParcel::SerializedParcel serialize(const WorkerCommitTasksRequest& parcel) override;
        IParcel::SerializedParcel serialize(const WorkerDownloadSceneRequest& parcel) override;
    };
}