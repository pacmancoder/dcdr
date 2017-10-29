#pragma once

#include <dcdr/Types.h>
#include <random>

namespace Dcdr::Utils
{
    class Rng
    {
    public:
        Rng();
        Rng(Types::Offset seed);

        Types::Real generate_real(Types::Real from, Types::Real to);
        Types::Size generate_int(Types::Size from, Types::Size to);
    private:
        std::default_random_engine random_engine_;
    };

}