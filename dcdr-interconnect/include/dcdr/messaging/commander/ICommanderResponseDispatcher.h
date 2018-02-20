#pragma once

#include <dcdr/messaging/InterconnectExceptions.h>

namespace Dcdr::Interconnect
{
    // job
    class CommanderGetJobListResponse;
    class CommanderGetJobInfoResponse;
    class CommanderGetJobArtifactResponse;
    // scene
    class CommanderGetSceneListResponse;
    // node
    class CommanderGetNodeListResponse;
    class CommanderGetNodeInfoResponse;
    // common
    class CommanderErrorResponse;
    class CommanderGetServerStatusResponse;

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
        virtual void dispatch(const CommanderGetJobArtifactResponse&)
        {
            dispatch_not_implemented("CommanderGetJobArtifactResponse");
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
        virtual void dispatch(const CommanderErrorResponse&)
        {
            dispatch_not_implemented("CommanderErrorResponse");
        }
        virtual void dispatch(const CommanderGetServerStatusResponse&)
        {
            dispatch_not_implemented("CommanderGetServerStatusResponse");
        }

        virtual void dispatch_not_implemented(const std::string& parcelKind)
        {
            throw DispatchNotImplemented(std::string("Dispatch not implemented for ").append(parcelKind));
        };

        virtual ~ICommanderResponseDispatcher() = default;
    };
}