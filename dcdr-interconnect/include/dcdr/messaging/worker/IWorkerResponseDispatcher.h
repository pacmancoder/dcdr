#pragma once

#include <dcdr/messaging/IParcel.h>
#include <dcdr/messaging/InterconnectExceptions.h>

namespace Dcdr::Interconnect
{
    class WorkerServerStatusResponse;
    class WorkerLoginResponse;
    class WorkerPollTasksResponse;
    class WorkerDownloadSceneResponse;

    class IWorkerResponseDispatcher
    {
    public:
        virtual void dispatch(const WorkerServerStatusResponse&)
        {
            dispatch_not_implemented("WorkerServerStatusResponse");
        }

        virtual void dispatch(const WorkerLoginResponse&)
        {
            dispatch_not_implemented("WorkerLoginResponse");
        }

        virtual void dispatch(const WorkerPollTasksResponse&)
        {
            dispatch_not_implemented("WorkerPollTasksResponse");
        }

        virtual void dispatch(const WorkerDownloadSceneResponse&)
        {
            dispatch_not_implemented("WorkerDownloadSceneResponse");
        }

        virtual void dispatch(const WorkerGetSceneInfoResponse&)
        {
            dispatch_not_implemented("WorkerGetSceneInfoResponse");
        }

        virtual void dispatch_not_implemented(const std::string& parcelKind)
        {
            throw DispatchNotImplemented(std::string("Dispatch not implemented for ").append(parcelKind));
        };

        virtual ~IWorkerResponseDispatcher() = default;
    };
}