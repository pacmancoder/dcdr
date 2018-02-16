#include "MongooseUtils.h"

using namespace Dcdr::Transport;

std::string Mongoose::socket_to_string(socket_address& socket)
{
    char str[16] = {};
    mg_sock_addr_to_str(&socket, str, sizeof(str), MG_SOCK_STRINGIFY_IP | MG_SOCK_STRINGIFY_PORT);
    return std::string(str);
}