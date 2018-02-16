#pragma once

#include <dcdr/messaging/IParcel.h>
#include <dcdr/messaging/InterconnectExceptions.h>

namespace Dcdr::Interconnect
{
    // jobs
    class CommanderGetJobListRequest;
    class CommanderGetJobInfoRequest;
    class CommanderGetJobPreviewRequest;
    class CommanderGetJobArtifactRequest;
    class CommanderSetJobStateRequest;
    class CommanderAddJobRequest;
    // scenes
    class CommanderGetSceneListRequest;
    // nodes
    class CommanderGetNodeListRequest;
    class CommanderGetNodeInfoRequest;
    class CommanderSetNodeStateRequest;

    class ICommanderRequestDispatcher
    {
    public:
        // jobs
        virtual IParcel::ParcelPtr dispatch(const CommanderGetJobListRequest&)
        {
            dispatch_not_implemented("CommanderGetJobListRequest");
            return nullptr;
        }
        virtual IParcel::ParcelPtr dispatch(const CommanderGetJobInfoRequest&)
        {
            dispatch_not_implemented("CommanderGetJobInfoRequest");
            return nullptr;
        }
        virtual IParcel::ParcelPtr dispatch(const CommanderGetJobPreviewRequest&)
        {
            dispatch_not_implemented("CommanderGetJobPreviewRequest");
            return nullptr;
        }
        virtual IParcel::ParcelPtr dispatch(const CommanderGetJobArtifactRequest&)
        {
            dispatch_not_implemented("CommanderGetJobArtifactRequest");
            return nullptr;
        }
        virtual IParcel::ParcelPtr dispatch(const CommanderSetJobStateRequest&)
        {
            dispatch_not_implemented("CommanderSetJobStateRequest");
            return nullptr;
        }
        virtual IParcel::ParcelPtr dispatch(const CommanderAddJobRequest&)
        {
            dispatch_not_implemented("CommanderAddJobRequest");
            return nullptr;
        }
        virtual IParcel::ParcelPtr dispatch(const CommanderGetSceneListRequest&)
        {
            dispatch_not_implemented("CommanderGetSceneListRequest");
            return nullptr;
        }
        // nodes
        virtual IParcel::ParcelPtr dispatch(const CommanderGetNodeListRequest&)
        {
            dispatch_not_implemented("CommanderGetNodeListRequest");
            return nullptr;
        }
        virtual IParcel::ParcelPtr dispatch(const CommanderGetNodeInfoRequest&)
        {
            dispatch_not_implemented("CommanderGetNodeInfoRequest");
            return nullptr;
        }
        virtual IParcel::ParcelPtr dispatch(const CommanderSetNodeStateRequest&)
        {
            dispatch_not_implemented("CommanderSetNodeStateRequest");
            return nullptr;
        }

        virtual void dispatch_not_implemented(const std::string& parcelKind)
        {
            throw DispatchNotImplemented(std::string("Dispatch not implemented for ").append(parcelKind));
        };

        virtual ~ICommanderRequestDispatcher() = default;

    };
}