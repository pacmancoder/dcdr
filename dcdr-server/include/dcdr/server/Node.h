#pragma once

#include <string>
#include <cstdint>
#include <map>

#include <dcdr/messaging/commander/CommanderInterconnectTypes.h>

namespace Dcdr::Server
{
    class Node
    {
    public:
        using PropertiesMap = std::map<std::string, std::string>;
        using State = Interconnect::Commander::NodeState;

    public:
        Node();

        void set_state(State state);
        State get_state();

        void add_property(const std::string& property, const std::string& value);
        void remove_property(const std::string& property);
        const PropertiesMap& get_properties();

    private:
        PropertiesMap properties_;
        State state_;
    };
}