#pragma once

#include <mongoose.h>
#include <string>

namespace Dcdr::Transport::Mongoose
{
    extern std::string socket_to_string(socket_address& socket);
}