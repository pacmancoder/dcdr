#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <dcdr/messaging/IParcel.h>

namespace Dcdr::Interconnect
{
    class AWorkerRequestParcel : public IParcel
    {
    public:
        using SessionID = std::array<uint8_t, 16>;
        using WorkerRequestParcelPtr = std::unique_ptr<AWorkerRequestParcel>;

    public:
        AWorkerRequestParcel();

        ParcelHandle dispatch(AParcelDispatcher &dispatcher) const override;

        void       set_session_id(const SessionID& sessionID);
        const SessionID& get_session_id() const;

    private:
        SessionID sessionID_;
    };
}