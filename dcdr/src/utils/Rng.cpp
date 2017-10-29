#include <dcdr/utils/Rng.h>

Dcdr::Utils::Rng::Rng()
{
    std::random_device random_device;
    random_engine_ = std::default_random_engine(random_device());
}

Dcdr::Utils::Rng::Rng(Dcdr::Types::Offset seed)
{
    random_engine_ = std::default_random_engine(seed);
}

Dcdr::Types::Real Dcdr::Utils::Rng::generate_real(Dcdr::Types::Real from, Dcdr::Types::Real to)
{
    std::uniform_real_distribution distribute(from, to);
    return distribute(random_engine_);
}

Dcdr::Types::Size Dcdr::Utils::Rng::generate_int(Dcdr::Types::Size from, Dcdr::Types::Size to)
{
    std::uniform_int_distribution distribute(from, to);
    return distribute(random_engine_);
}