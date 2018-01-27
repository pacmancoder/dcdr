#include <dcdr/messaging/AParcelDispatcher.h>

using namespace Dcdr::Interconnect;

// Definition generator to avoid boilerplate code
#define DISPATCH_NOT_IMPLEMENTED(__TARGET_CLASS__) \
    IParcel::ParcelHandle AParcelDispatcher::dispatch(const __TARGET_CLASS__&)\
    {\
        return dispatch_not_supported();\
    }\

IParcel::ParcelHandle AParcelDispatcher::dispatch_not_supported() { return IParcel::ParcelHandle(); }

DISPATCH_NOT_IMPLEMENTED(AWorkerRequestParcel)
DISPATCH_NOT_IMPLEMENTED(ACommanderRequestParcel)
DISPATCH_NOT_IMPLEMENTED(ACommanderResponseParcel)
