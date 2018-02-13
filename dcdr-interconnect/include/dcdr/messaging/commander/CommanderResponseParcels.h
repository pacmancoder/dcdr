#pragma once

#include <dcdr/messaging/commander/ACommanderResponseParcel.h>
#include <dcdr/messaging/commander/CommanderResponses.h>

#include <dcdr/messaging/commander/ICommanderResponseDispatcher.h>
#include <dcdr/messaging/commander/ICommanderResponseSerializer.h>

namespace Dcdr::Interconnect
{
    template <class ParcelDetails>
    class ConcreteCommanderResponseParcel : public ACommanderResponseParcel
    {
    public:
        template <typename... Args>
        explicit ConcreteCommanderResponseParcel(Args&&... args) :
                details_(std::forward<Args>(args)...) {}

        SerializedParcel serialize(ICommanderResponseSerializer& serializer) const override
        {
            return serializer.serialize(details_);
        }

        ParcelHandle dispatch(ICommanderResponseDispatcher& dispatcher) const override
        {
            return dispatcher.dispatch(details_);
        }

        const ParcelDetails& get_response() const
        {
            return details_;
        }

    private:
        ParcelDetails details_;
    };

    using CommanderGetJobListResponseParcel = ConcreteCommanderResponseParcel<CommanderGetJobListResponse>;
    using CommanderGetJobInfoResponseParcel = ConcreteCommanderResponseParcel<CommanderGetJobInfoResponse>;
    using CommanderGetJobPreviewResponseParcel = ConcreteCommanderResponseParcel<CommanderGetJobPreviewResponse>;
    using CommanderGetJobArtifactResponseParcel = ConcreteCommanderResponseParcel<CommanderGetJobArtifactResponse>;
    using CommanderDoJobListUpdateResponseParcel = ConcreteCommanderResponseParcel<CommanderDoJobListUpdateResponse>;
    using CommanderGetSceneListReponseParcel = ConcreteCommanderResponseParcel<CommanderGetSceneListResponse>;
    using CommanderGetNodeListResponseParcel = ConcreteCommanderResponseParcel<CommanderGetNodeListResponse>;
    using CommanderGetNodeInfoResponseParcel = ConcreteCommanderResponseParcel<CommanderGetNodeInfoResponse>;
    using CommanderDoNodeListUpdateResponseParcel = ConcreteCommanderResponseParcel<CommanderDoNodeListUpdateResponse>;
    using CommanderDoShowErrorResponseParcel = ConcreteCommanderResponseParcel<CommanderDoShowErrorResponse>;
}