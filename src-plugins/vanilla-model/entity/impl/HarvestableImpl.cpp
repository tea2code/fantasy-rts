#include "HarvestableImpl.h"


frts::HarvestableImpl::HarvestableImpl(IdPtr componentType)
    : componentType{componentType}
{

}

frts::HarvestableImpl::~HarvestableImpl()
{

}

void frts::HarvestableImpl::addType(IdPtr type)
{
    assert(type != nullptr);

    types.insert(type);
}

frts::IdPtr frts::HarvestableImpl::getComponentType() const
{
    return componentType;
}

double frts::HarvestableImpl::getSpeed() const
{
    return speed;
}

frts::IdUnorderedSet frts::HarvestableImpl::getTypes() const
{
    return types;
}

bool frts::HarvestableImpl::hasType(IdPtr type) const
{
    assert(type != nullptr);

    return (types.find(type) != types.end());
}

void frts::HarvestableImpl::removeType(IdPtr type)
{
    assert(type != nullptr);

    types.erase(type);
}

void frts::HarvestableImpl::setSpeed(double speed)
{
    this->speed = speed;
}
