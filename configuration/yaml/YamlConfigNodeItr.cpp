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
    iterator++;
    return this;
}

frts::ConfigNodeItr::self_type* frts::YamlConfigNodeItr::operator++(int)
{
    iterator++;
    return this;
}

frts::ConfigNodeItr::reference frts::YamlConfigNodeItr::operator*()
{
    frts::ConfigNodeItr::reference itr = frts::ConfigNodePtr(new YamlConfigNode(*iterator));
    return itr;
}

frts::ConfigNodeItr::pointer frts::YamlConfigNodeItr::operator->()
{
    frts::ConfigNodeItr::pointer itr = frts::ConfigNodePtr(new YamlConfigNode(*iterator));
    return itr;
}

bool frts::YamlConfigNodeItr::operator==(const self_type& rhs)
{
    return iterator == dynamic_cast<const YamlConfigNodeItr&>(rhs).iterator;
}

bool frts::YamlConfigNodeItr::operator!=(const self_type& rhs)
{
    return iterator != dynamic_cast<const YamlConfigNodeItr&>(rhs).iterator;
}
