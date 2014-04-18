#include "YamlConfigNodeItr.h"

#include "YamlConfigNode.h"

#include <stdexcept>


frts::YamlConfigNodeItr::YamlConfigNodeItr(YAML::Node::iterator iterator)
    : iterator{iterator}
{
}

frts::YamlConfigNodeItr::~YamlConfigNodeItr()
{
}

frts::ConfigNodeItr::self_type* frts::YamlConfigNodeItr::operator++()
{
    ++iterator;
    return this;
}

frts::ConfigNodeItr::self_type* frts::YamlConfigNodeItr::operator++(int)
{
    frts::ConfigNodeItr::self_type* copy = new YamlConfigNodeItr(iterator);
    ++iterator;
    return copy;
}

frts::ConfigNodeItr::reference frts::YamlConfigNodeItr::operator*()
{
    return frts::ConfigNodePtr(new YamlConfigNode(*iterator));
}

frts::ConfigNodeItr::pointer frts::YamlConfigNodeItr::operator->()
{
    return frts::ConfigNodePtr(new YamlConfigNode(*iterator));
}

bool frts::YamlConfigNodeItr::operator==(const self_type& rhs)
{
    return iterator == dynamic_cast<const YamlConfigNodeItr&>(rhs).iterator;
}

bool frts::YamlConfigNodeItr::operator!=(const self_type& rhs)
{
    return iterator != dynamic_cast<const YamlConfigNodeItr&>(rhs).iterator;
}
