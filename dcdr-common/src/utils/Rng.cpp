#include <dcdr/utils/Rng.h>

Dcdr::Utils::Rng::Rng() :
    random_engine_(std::random_device{} ()) {}

Dcdr::Utils::Rng::Rng(Dcdr::Types::Offset seed) :
        random_engine_(seed) {}

Dcdr::Types::Real Dcdr::Utils::Rng::generate_real(Dcdr::Types::Real from, Dcdr::Types::Real to)
{
    std::uniform_real_distribution<Dcdr::Types::Real> distribute(from, to);
    return distribute(random_engine_);
}

Dcdr::Types::Size Dcdr::Utils::Rng::generate_int(Dcdr::Types::Size from, Dcdr::Types::Size to)
{
    std::uniform_int_distribution<Dcdr::Types::Size> distribute(from, to);
    return distribute(random_engine_);
}