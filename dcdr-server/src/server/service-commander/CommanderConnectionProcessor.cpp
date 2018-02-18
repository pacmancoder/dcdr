#include <dcdr/server/service-commander/CommanderConnectionProcessor.h>

#include <dcdr/server/core/CoreContext.h>

#include <dcdr/messaging/flatbuffers/FlatBuffersParcelSerializer.h>
#include <dcdr/messaging/flatbuffers/FlatBuffersParcelDeserializer.h>

#include <dcdr/messaging/commander/CommanderRequestParcels.h>
#include <dcdr/messaging/commander/CommanderResponseParcels.h>

using namespace Dcdr::Server;
using namespace Dcdr::Transport;
using namespace Dcdr::Interconnect;


CommanderConnectionProcessor::CommanderConnectionProcessor(std::shared_ptr<CoreContext>& coreContext) :
    IAsyncConnectionProcessor(),
    IParcelDispatcher(),
    ICommanderRequestDispatcher(),
    coreContext_(coreContext) {}


uint32_t CommanderConnectionProcessor::open_connection()
{
    return coreContext_->get_connections().add(Connection());
}

IAsyncConnectionProcessor::ResponseHandle CommanderConnectionProcessor::get_response(
        uint32_t, const IAsyncConnectionProcessor::Request& request)
{
    FlatBuffersParcelDeserializer deserializer;
    auto requestParcel = deserializer.deserialize(request);
    if (requestParcel == nullptr)
    {
        return IAsyncConnectionProcessor::ResponseHandle();
    }

    auto responseParcel = requestParcel->dispatch(*this);
    if  (responseParcel == nullptr)
    {
        return IAsyncConnectionProcessor::ResponseHandle();
    }

    FlatBuffersParcelSerializer serializer;
    std::promise<Response> responsePromise;
    responsePromise.set_value(responseParcel->serialize(serializer));

    return responsePromise.get_future();
}

void CommanderConnectionProcessor::close_connection(uint32_t id)
{
    coreContext_->get_connections().remove(id);
}

IParcel::ParcelPtr CommanderConnectionProcessor::dispatch(const Dcdr::Interconnect::ACommanderRequestParcel& parcel)
{
    return parcel.dispatch(static_cast<Interconnect::ICommanderRequestDispatcher&>(*this));
}

IParcel::ParcelPtr CommanderConnectionProcessor::dispatch(const CommanderGetJobListRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}

IParcel::ParcelPtr CommanderConnectionProcessor::dispatch(const CommanderGetJobInfoRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}

IParcel::ParcelPtr CommanderConnectionProcessor::dispatch(const CommanderGetJobPreviewRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}

IParcel::ParcelPtr CommanderConnectionProcessor::dispatch(const CommanderGetJobArtifactRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}

IParcel::ParcelPtr CommanderConnectionProcessor::dispatch(const CommanderSetJobStateRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}

IParcel::ParcelPtr CommanderConnectionProcessor::dispatch(const CommanderAddJobRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}

IParcel::ParcelPtr CommanderConnectionProcessor::dispatch(const CommanderGetSceneListRequest&)
{
    std::vector<Interconnect::Commander::Scene> scenes_;

    coreContext_->get_scenes().iterate_const([&scenes_](uint32_t id, const Scene& scene)
    {
       scenes_.push_back(Interconnect::Commander::Scene{id, scene.get_name(), scene.get_width(), scene.get_height()});
    });

    return std::make_unique<CommanderGetSceneListReponseParcel>(std::move(scenes_));
}

IParcel::ParcelPtr CommanderConnectionProcessor::dispatch(const CommanderGetNodeListRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}

IParcel::ParcelPtr CommanderConnectionProcessor::dispatch(const CommanderGetNodeInfoRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}

IParcel::ParcelPtr CommanderConnectionProcessor::dispatch(const CommanderSetNodeStateRequest& request)
{
    return ICommanderRequestDispatcher::dispatch(request);
}
