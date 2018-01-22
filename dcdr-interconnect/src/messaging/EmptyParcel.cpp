#include <dcdr/messaging/EmptyParcel.h>

using namespace Dcdr::Interconnect;

IParcel::ParcelHandle EmptyParcel::dispatch(IParcelDispatcher &dispatcher)
{
    // Return future without shared state
    return IParcel::ParcelHandle();
}
