#include <dcdr/messaging/commander/ACommanderRequestParcelDispatcher.h>

using namespace Dcdr::Interconnect;

// Definition generator to avoid boilerplate code
#define DISPATCH_NOT_IMPLEMENTED(__TARGET_CLASS__) \
    IParcel::ParcelHandle ACommanderRequestParcelDispatcher::dispatch(const __TARGET_CLASS__&)\
    {\
        return dispatch_not_supported();\
    }\

IParcel::ParcelHandle ACommanderRequestParcelDispatcher::dispatch_not_supported() { return IParcel::ParcelHandle(); }

DISPATCH_NOT_IMPLEMENTED(CommanderGetSurfaceInfoRequest)
DISPATCH_NOT_IMPLEMENTED(CommanderGetSurfaceRequest)