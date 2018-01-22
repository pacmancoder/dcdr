#pragma once

#include <array>
#include <cstdint>
#include <dcdr/messaging/AWorkerRequestParcel.h>

namespace Dcdr::Interconnect
{
    class WorkerConnectRequest : public AWorkerRequestParcel
    {
    public:
        using Token = std::array<uint8_t, 16>;

    public:
        WorkerConnectRequest();

        void set_token(const Token& token);
        const Token& get_token() const;

        SerializedParcel serialize(AParcelSerializer& dispatcher) override;

    private:
        Token token_;
    };
}