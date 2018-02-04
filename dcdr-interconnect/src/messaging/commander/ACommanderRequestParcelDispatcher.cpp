#include <dcdr/messaging/commander/ACommanderRequestParcelDispatcher.h>

using namespace Dcdr::Interconnect;

// Definition generator to avoid boilerplate code
#define IMPLEMENT_DEFAULT_DISPATCH(__TARGET_CLASS__) \
    IParcel::ParcelHandle ACommanderRequestParcelDispatcher::dispatch(const __TARGET_CLASS__&)\
    {\
        return dispatch_not_supported();\
    }\

IParcel::ParcelHandle ACommanderRequestParcelDispatcher::dispatch_not_supported() { return IParcel::ParcelHandle(); }

IMPLEMENT_DEFAULT_DISPATCH(CommanderGetJobListRequest)
IMPLEMENT_DEFAULT_DISPATCH(CommanderGetJobInfoRequest)
IMPLEMENT_DEFAULT_DISPATCH(CommanderGetJobPreviewRequest)
IMPLEMENT_DEFAULT_DISPATCH(CommanderGetJobArtifactRequest)
IMPLEMENT_DEFAULT_DISPATCH(CommanderSetJobStateRequest)
IMPLEMENT_DEFAULT_DISPATCH(CommanderAddJobRequest)
IMPLEMENT_DEFAULT_DISPATCH(CommanderGetSceneListRequest)
IMPLEMENT_DEFAULT_DISPATCH(CommanderGetNodeListRequest)
IMPLEMENT_DEFAULT_DISPATCH(CommanderGetNodeInfoRequest)
IMPLEMENT_DEFAULT_DISPATCH(CommanderSetNodeStateRequest)