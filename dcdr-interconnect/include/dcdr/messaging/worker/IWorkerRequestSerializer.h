#pragma once

#include <dcdr/messaging/IParcel.h>


namespace Dcdr::Interconnect
{
    class WorkerLoginRequest;
    class WorkerLogoutRequest;
    class WorkerSendHardwareInfoRequest;
    class WorkerPollTasksRequest;
    class WorkerCommitTasksRequest;
    class WorkerDownloadSceneRequest;

    class IWorkerRequestSerializer
    {
    public:
        virtual IParcel::SerializedParcel serialize(const WorkerLoginRequest& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const WorkerLogoutRequest& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const WorkerSendHardwareInfoRequest& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const WorkerPollTasksRequest& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const WorkerCommitTasksRequest& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const WorkerDownloadSceneRequest& parcel) = 0;

        virtual ~IWorkerRequestSerializer() = default;
    };
}