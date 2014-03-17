#include "YamlConfigNodeItr.h"

#include <stdexcept>

frts::YamlConfigNodeItr::YamlConfigNodeItr()
{

}

frts::YamlConfigNodeItr::~YamlConfigNodeItr()
{

}

frts::ConfigNodeItr::self_type* frts::YamlConfigNodeItr::operator++()
{
    throw std::runtime_error("");
}

frts::ConfigNodeItr::self_type* frts::YamlConfigNodeItr::operator++(int)
{
    throw std::runtime_error("");
}

frts::ConfigNodeItr::reference frts::YamlConfigNodeItr::operator*()
{
    throw std::runtime_error("");
}

frts::ConfigNodeItr::pointer frts::YamlConfigNodeItr::operator->()
{
    throw std::runtime_error("");
}

bool frts::YamlConfigNodeItr::operator==(const self_type& rhs)
{
    throw std::runtime_error("");
}

bool frts::YamlConfigNodeItr::operator!=(const self_type& rhs)
{
    throw std::runtime_error("");
}
