#include <dcdr/messaging/commander/CommanderRequests.h>
#include <dcdr/messaging/AParcelSerializer.h>
#include <dcdr/messaging/commander/ACommanderRequestParcelDispatcher.h>

using namespace Dcdr::Interconnect;

#define IMPLEMENT_VISITORS(__TARGET_CLASS__) \
\
IParcel::SerializedParcel __TARGET_CLASS__::serialize(AParcelSerializer& serializer) const\
{\
    return serializer.serialize(*this);\
}\
\
IParcel::ParcelHandle __TARGET_CLASS__::dispatch(ACommanderRequestParcelDispatcher& dispatcher) const\
{\
    return dispatcher.dispatch(*this);\
}\

IMPLEMENT_VISITORS(CommanderGetJobListRequest)
IMPLEMENT_VISITORS(CommanderGetJobInfoRequest)
IMPLEMENT_VISITORS(CommanderGetJobPreviewRequest)
IMPLEMENT_VISITORS(CommanderGetJobArtifactRequest)
IMPLEMENT_VISITORS(CommanderSetJobStateRequest)
IMPLEMENT_VISITORS(CommanderAddJobRequest)
IMPLEMENT_VISITORS(CommanderGetSceneListRequest)
IMPLEMENT_VISITORS(CommanderGetNodeListRequest)
IMPLEMENT_VISITORS(CommanderGetNodeInfoRequest)
IMPLEMENT_VISITORS(CommanderSetNodeStateRequest)