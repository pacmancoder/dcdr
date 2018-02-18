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
        Node(Node&& rhs) = default;

        void set_state(State state);
        State get_state() const;

        void set_property(const std::string &property, const std::string &value);
        std::string get_property(const std::string& property) const;
        const PropertiesMap& get_all_properties() const;
        void remove_property(const std::string& property);

    private:
        PropertiesMap properties_;
        State state_;
    };
}