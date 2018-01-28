#include <dcdr/messaging/worker/AWorkerRequestParcel.h>

#include <algorithm>

#include <dcdr/messaging/AParcelDispatcher.h>
#include <dcdr/messaging/AParcelSerializer.h>

using namespace Dcdr::Interconnect;

IParcel::ParcelHandle AWorkerRequestParcel::dispatch(AParcelDispatcher& dispatcher) const
{
    return dispatcher.dispatch(*this);
}

AWorkerRequestParcel::AWorkerRequestParcel() :
        sessionID_()
{
    std::fill(sessionID_.begin(), sessionID_.end(), 0);
}

void AWorkerRequestParcel::set_session_id(const SessionID& sessionID)
{
    sessionID_ = sessionID;
}

const AWorkerRequestParcel::SessionID& AWorkerRequestParcel::get_session_id() const
{
    return sessionID_;
}