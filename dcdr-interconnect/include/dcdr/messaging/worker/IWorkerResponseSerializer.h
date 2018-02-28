#pragma once

#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{
    class WorkerServerStatusResponse;
    class WorkerLoginResponse;
    class WorkerPollTasksResponse;
    class WorkerDownloadSceneResponse;

    class IWorkerResponseSerializer
    {
    public:
        virtual IParcel::SerializedParcel serialize(const WorkerServerStatusResponse& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const WorkerLoginResponse& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const WorkerPollTasksResponse& parcel) = 0;
        virtual IParcel::SerializedParcel serialize(const WorkerDownloadSceneResponse& parcel) = 0;

        virtual ~IWorkerResponseSerializer() = default;
    };
}