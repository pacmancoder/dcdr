#include <dcdr/server/service-worker/WorkerService.h>

#include <dcdr/messaging/flatbuffers/FlatBuffersParcelDeserializer.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>

using namespace Dcdr::Server;
using namespace Dcdr::Transport;
using namespace Dcdr::Interconnect;

WorkerService::WorkerService(const std::shared_ptr<CoreContext>& coreContext) :
        coreContext_(coreContext),
        routers_()
{

}

uint32_t WorkerService::open_connection()
{
    auto router = std::make_unique<WorkerRouter>(coreContext_);
    auto connectionId = router->get_connection_id();

    routers_.emplace(connectionId, std::move(router));

    return connectionId;
}

IAsyncConnectionProcessor::ResponseHandle WorkerService::get_response(
        uint32_t connectionId, const IAsyncConnectionProcessor::Request& request)
{
    FlatBuffersParcelDeserializer deserializer;
    auto requestParcel = deserializer.deserialize(request);
    if (requestParcel == nullptr) // deserialization succeeded, but parcel is empty
    {
        return IAsyncConnectionProcessor::ResponseHandle();
    }

    auto responseParcel = requestParcel->dispatch(*routers_.at(connectionId));
    if  (responseParcel == nullptr) // dispatch succeeded, but response is empty
    {
        return IAsyncConnectionProcessor::ResponseHandle();
    }

    FlatBuffersParcelSerializer serializer;
    std::promise<Response> responsePromise;
    responsePromise.set_value(responseParcel->serialize(serializer));

    return responsePromise.get_future();
}

void WorkerService::close_connection(uint32_t id)
{
    routers_.erase(id);
}
