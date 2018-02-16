#pragma once

#include <dcdr/messaging/InterconnectExceptions.h>

namespace Dcdr::Interconnect
{
    // job
    class CommanderGetJobListResponse;
    class CommanderGetJobInfoResponse;
    class CommanderGetJobPreviewResponse;
    class CommanderGetJobArtifactResponse;
    class CommanderDoJobListUpdateResponse;
    // scene
    class CommanderGetSceneListResponse;
    // node
    class CommanderGetNodeListResponse;
    class CommanderGetNodeInfoResponse;
    class CommanderDoNodeListUpdateResponse;
    // common
    class CommanderDoShowErrorResponse;

    class ICommanderResponseDispatcher
    {
    public:

        virtual void dispatch(const CommanderGetJobListResponse&)
        {
            dispatch_not_implemented("CommanderGetJobListResponse");
        }
        virtual void dispatch(const CommanderGetJobInfoResponse&)
        {
            dispatch_not_implemented("CommanderGetJobInfoResponse");
        }
        virtual void dispatch(const CommanderGetJobPreviewResponse&)
        {
            dispatch_not_implemented("CommanderGetJobPreviewResponse");
        }
        virtual void dispatch(const CommanderGetJobArtifactResponse&)
        {
            dispatch_not_implemented("CommanderGetJobArtifactResponse");
        }
        virtual void dispatch(const CommanderDoJobListUpdateResponse&)
        {
            dispatch_not_implemented("CommanderDoJobListUpdateResponse");
        }
        virtual void dispatch(const CommanderGetSceneListResponse&)
        {
            dispatch_not_implemented("CommanderGetSceneListResponse");
        }
        virtual void dispatch(const CommanderGetNodeListResponse&)
        {
            dispatch_not_implemented("CommanderGetNodeListResponse");
        }
        virtual void dispatch(const CommanderGetNodeInfoResponse&)
        {
            dispatch_not_implemented("CommanderGetNodeInfoResponse");
        }
        virtual void dispatch(const CommanderDoNodeListUpdateResponse&)
        {
            dispatch_not_implemented("CommanderDoNodeListUpdateResponse");
        }
        virtual void dispatch(const CommanderDoShowErrorResponse&)
        {
            dispatch_not_implemented("CommanderDoShowErrorResponse");
        }

        virtual void dispatch_not_implemented(const std::string& parcelKind)
        {
            throw DispatchNotImplemented(std::string("Dispatch not implemented for ").append(parcelKind));
        };

        virtual ~ICommanderResponseDispatcher() = default;
    };
}