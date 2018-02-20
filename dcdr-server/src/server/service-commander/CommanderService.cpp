#include <dcdr/server/service-commander/CommanderService.h>

#include <dcdr/server/core/CoreContext.h>

#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelDeserializer.h>

#include <dcdr/messaging/commander/CommanderRequestParcels.h>
#include <dcdr/messaging/commander/CommanderResponseParcels.h>

using namespace Dcdr::Server;
using namespace Dcdr::Transport;
using namespace Dcdr::Interconnect;


CommanderService::CommanderService(std::shared_ptr<CoreContext>& coreContext) :
    IAsyncConnectionProcessor(),
    coreContext_(coreContext),
    commanderRouter_(std::make_shared<CommanderRouter>(coreContext)) {}


uint32_t CommanderService::open_connection()
{
    return coreContext_->get_connections().add(Connection());
}

IAsyncConnectionProcessor::ResponseHandle CommanderService::get_response(
        uint32_t, const IAsyncConnectionProcessor::Request& request)
{
    FlatBuffersParcelDeserializer deserializer;
    auto requestParcel = deserializer.deserialize(request);
    if (requestParcel == nullptr) // deserialization succeeded, but parcel is empty
    {
        return IAsyncConnectionProcessor::ResponseHandle();
    }

    auto responseParcel = requestParcel->dispatch(*commanderRouter_);
    if  (responseParcel == nullptr) // dispatch succeeded, but response is empty
    {
        return IAsyncConnectionProcessor::ResponseHandle();
    }

    FlatBuffersParcelSerializer serializer;
    std::promise<Response> responsePromise;
    responsePromise.set_value(responseParcel->serialize(serializer));

    return responsePromise.get_future();
}

void CommanderService::close_connection(uint32_t id)
{
    coreContext_->get_connections().remove(id);
}