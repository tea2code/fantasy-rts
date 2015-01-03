#include "InfoImpl.h"


frts::InfoImpl::InfoImpl(IdPtr type)
    : type{type}
{

}

frts::IdPtr frts::InfoImpl::getComponentType() const
{
    return type;
}

std::vector<frts::Info::InfoItem> frts::InfoImpl::getInformation() const
{
    return information;
}

void frts::InfoImpl::setInformation(std::vector<InfoItem> values)
{
    this->information = values;
}
