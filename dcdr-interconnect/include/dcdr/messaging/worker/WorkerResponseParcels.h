#pragma once

#include <dcdr/messaging/worker/WorkerResponses.h>
#include <dcdr/messaging/worker/AWorkerResponseParcel.h>
#include <dcdr/messaging/worker/IWorkerResponseDispatcher.h>
#include <dcdr/messaging/worker/IWorkerResponseSerializer.h>

namespace Dcdr::Interconnect
{
    template <class ParcelDetails>
    class ConcreteWorkerResponseParcel : public AWorkerResponseParcel
    {
    public:
        template <typename... Args>
        explicit ConcreteWorkerResponseParcel(Args&&... args) :
                details_(std::forward<Args>(args)...) {}

        IParcel::SerializedParcel serialize(IWorkerResponseSerializer& serializer) const override
        {
            return serializer.serialize(details_);
        }

        IParcel::ParcelPtr dispatch(IWorkerResponseDispatcher& dispatcher) const override
        {
            dispatcher.dispatch(details_);
            return nullptr;
        }

        const ParcelDetails& get_response() const
        {
            return details_;
        }

    private:
        ParcelDetails details_;
    };

    using WorkerServerStatusResponseParcel = ConcreteWorkerResponseParcel<WorkerServerStatusResponse>;
    using WorkerLoginResponseParcel = ConcreteWorkerResponseParcel<WorkerLoginResponse>;
    using WorkerPollTasksResponseParcel = ConcreteWorkerResponseParcel<WorkerPollTasksResponse>;
    using WorkerDownloadSceneResponseParcel = ConcreteWorkerResponseParcel<WorkerDownloadSceneResponse>;
    using WorkerGetSceneInfoResponseParcel = ConcreteWorkerResponseParcel<WorkerGetSceneInfoResponse>;
}