#pragma once

#include <dcdr/messaging/IParcel.h>
#include <dcdr/messaging/InterconnectExceptions.h>

namespace Dcdr::Interconnect
{
    class WorkerLoginRequest;
    class WorkerLogoutRequest;
    class WorkerSendHardwareInfoRequest;
    class WorkerPollTasksRequest;
    class WorkerCommitTasksRequest;
    class WorkerDownloadSceneRequest;

    class IWorkerRequestDispatcher
    {
    public:
        virtual IParcel::ParcelPtr dispatch(const WorkerLoginRequest&)
        {
            dispatch_not_implemented("WorkerLoginRequest");
            return nullptr;
        }

        virtual IParcel::ParcelPtr dispatch(const WorkerLogoutRequest&)
        {
            dispatch_not_implemented("WorkerLogoutRequest");
            return nullptr;
        }

        virtual IParcel::ParcelPtr dispatch(const WorkerSendHardwareInfoRequest&)
        {
            dispatch_not_implemented("WorkerSendHardwareInfoRequest");
            return nullptr;
        }

        virtual IParcel::ParcelPtr dispatch(const WorkerPollTasksRequest&)
        {
            dispatch_not_implemented("WorkerPollTasksRequest");
            return nullptr;
        }

        virtual IParcel::ParcelPtr dispatch(const WorkerCommitTasksRequest&)
        {
            dispatch_not_implemented("WorkerCommitTasksRequest");
            return nullptr;
        }

        virtual IParcel::ParcelPtr dispatch(const WorkerDownloadSceneRequest&)
        {
            dispatch_not_implemented("WorkerDownloadSceneRequest");
            return nullptr;
        }

        virtual void dispatch_not_implemented(const std::string& parcelKind)
        {
            throw DispatchNotImplemented(std::string("Dispatch not implemented for ").append(parcelKind));
        };

        virtual ~IWorkerRequestDispatcher() = default;
    };
}