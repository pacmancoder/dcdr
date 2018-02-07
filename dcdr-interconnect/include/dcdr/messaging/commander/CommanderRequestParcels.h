#pragma once

#include <dcdr/messaging/commander/ACommanderRequestParcel.h>
#include <dcdr/messaging/commander/CommanderRequests.h>

namespace Dcdr::Interconnect
{
    class ICommanderRequestSerializer;
    class ICommanderRequestDispatcher;


    template <class ParcelDetails, typename... Args>
    class ConcreteCommanderRequestParcel : public ACommanderRequestParcel
    {
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