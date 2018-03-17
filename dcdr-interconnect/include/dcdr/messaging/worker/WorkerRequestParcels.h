#pragma once

#include <dcdr/messaging/worker/WorkerRequests.h>
#include <dcdr/messaging/worker/AWorkerRequestParcel.h>
#include <dcdr/messaging/worker/IWorkerRequestDispatcher.h>
#include <dcdr/messaging/worker/IWorkerRequestSerializer.h>

namespace Dcdr::Interconnect
{

    template <class ParcelDetails>
    class ConcreteWorkerRequestParcel : public AWorkerRequestParcel
    {
    public:
        template <typename... Args>
        explicit ConcreteWorkerRequestParcel(Args&&... args) :
                details_(std::forward<Args>(args)...) {}

        IParcel::SerializedParcel serialize(IWorkerRequestSerializer& serializer) const override
        {
            return serializer.serialize(details_);
        }

        IParcel::ParcelPtr dispatch(IWorkerRequestDispatcher& dispatcher) const override
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

    using WorkerLoginRequestParcel = ConcreteWorkerRequestParcel<WorkerLoginRequest>;
    using WorkerLogoutRequestParcel = ConcreteWorkerRequestParcel<WorkerLogoutRequest>;
    using WorkerSendHardwareInfoRequestParcel = ConcreteWorkerRequestParcel<WorkerSendHardwareInfoRequest>;
    using WorkerPollTasksRequestParcel = ConcreteWorkerRequestParcel<WorkerPollTasksRequest>;
    using WorkerCommitTasksRequestParcel = ConcreteWorkerRequestParcel<WorkerCommitTasksRequest>;
    using WorkerDownloadSceneRequestParcel = ConcreteWorkerRequestParcel<WorkerDownloadSceneRequest>;
    using WorkerGetSceneInfoRequestParcel = ConcreteWorkerRequestParcel<WorkerGetSceneInfoRequest>;

}