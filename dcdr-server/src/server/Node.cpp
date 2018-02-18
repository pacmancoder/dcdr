#include <dcdr/server/Node.h>

using namespace Dcdr::Server;

Node::Node() :
    properties_(),
    state_(State::Active) {}

void Node::set_state(Node::State state)
{
    state_ = state;
}

Node::State Node::get_state() const
{
    return state_;
}

void Node::set_property(const std::string &property, const std::string &value)
{
    properties_[property] = value;
}

void Node::remove_property(const std::string& property)
{
    properties_.erase(property);
}

const Node::PropertiesMap& Node::get_all_properties() const
{
    return properties_;
}

std::string Node::get_property(const std::string &property) const
{
    const auto foundProperty = properties_.find(property);
    if (foundProperty != properties_.cend())
    {
        return foundProperty->second;
    }

    return std::string();
}
