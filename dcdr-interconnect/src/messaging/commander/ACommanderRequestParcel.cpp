#include <dcdr/messaging/commander/ACommanderRequestParcel.h>

#include <dcdr/messaging/AParcelDispatcher.h>

using namespace Dcdr::Interconnect;

IParcel::ParcelHandle ACommanderRequestParcel::dispatch(AParcelDispatcher& dispatcher) const
{
    return dispatcher.dispatch(*this);
}
