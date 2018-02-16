#include <dcdr/server/Node.h>

using namespace Dcdr::Server;

Node::Node() :
    properties_(),
    state_(State::Active) {}

void Node::set_state(Node::State state)
{
    state_ = state;
}

Node::State Node::get_state()
{
    return state_;
}

void Node::add_property(const std::string& property, const std::string& value)
{
    properties_[property] = value;
}

void Node::remove_property(const std::string& property)
{
    properties_.erase(property);
}

const Node::PropertiesMap& Node::get_properties()
{
    return properties_;
}
