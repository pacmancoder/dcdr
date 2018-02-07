#pragma once

#include <dcdr/messaging/commander/ACommanderRequestParcel.h>
#include <dcdr/messaging/commander/CommanderRequests.h>

#include <dcdr/messaging/commander/ICommanderRequestSerializer.h>
#include <dcdr/messaging/commander/ICommanderRequestDispatcher.h>

namespace Dcdr::Interconnect
{
    template <class ParcelDetails>
    class ConcreteCommanderRequestParcel : public ACommanderRequestParcel
    {
    public:
        template <typename... Args>
        explicit ConcreteCommanderRequestParcel(Args&&... args) :
                details_(std::forward<Args>(args)...) {}

        SerializedParcel serialize(ICommanderRequestSerializer& serializer) const override
        {
            return serializer.serialize(details_);
        }

        ParcelHandle dispatch(ICommanderRequestDispatcher& dispatcher) const override
        {
            return dispatcher.dispatch(details_);
        }

        const ParcelDetails& get_request() const
        {
            return details_;
        }

    private:
        ParcelDetails details_;
    };

    using CommanderGetJobListRequestParcel = ConcreteCommanderRequestParcel<CommanderGetJobListRequest>;
    using CommanderGetJobInfoRequestParcel = ConcreteCommanderRequestParcel<CommanderGetJobInfoRequest>;
    using CommanderGetJobPreviewRequestParcel = ConcreteCommanderRequestParcel<CommanderGetJobPreviewRequest>;
    using CommanderGetJobArtifactRequestParcel = ConcreteCommanderRequestParcel<CommanderGetJobArtifactRequest>;
    using CommanderSetJobStateRequestParcel = ConcreteCommanderRequestParcel<CommanderSetJobStateRequest>;
    using CommanderAddJobRequestParcel = ConcreteCommanderRequestParcel<CommanderAddJobRequest>;
    using CommanderGetSceneListRequestParcel = ConcreteCommanderRequestParcel<CommanderGetSceneListRequest>;
    using CommanderGetNodeListRequestParcel = ConcreteCommanderRequestParcel<CommanderGetNodeListRequest>;
    using CommanderGetNodeInfoRequestParcel = ConcreteCommanderRequestParcel<CommanderGetNodeInfoRequest>;
    using CommanderSetNodeStateRequestParcel = ConcreteCommanderRequestParcel<CommanderSetNodeStateRequest>;
}