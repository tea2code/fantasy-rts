#include "HarvestableImpl.h"


frts::HarvestableImpl::HarvestableImpl(const IdPtr& componentType)
    : componentType{componentType}
{

}

frts::HarvestableImpl::~HarvestableImpl()
{

}

void frts::HarvestableImpl::addType(const IdPtr& type)
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

bool frts::HarvestableImpl::hasType(const IdPtr& type) const
{
    assert(type != nullptr);

    return (types.find(type) != types.end());
}

void frts::HarvestableImpl::removeType(const IdPtr& type)
{
    assert(type != nullptr);

    types.erase(type);
}

void frts::HarvestableImpl::setSpeed(double speed)
{
    this->speed = speed;
}
