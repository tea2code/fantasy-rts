#include "EntityGroupSatelliteImpl.h"


frts::EntityGroupSatelliteImpl::EntityGroupSatelliteImpl(const IdPtr& componentType, const EntityPtr& master)
    : componentType{componentType}, master{master}
{

}

frts::EntityGroupSatelliteImpl::~EntityGroupSatelliteImpl()
{

}

frts::IdPtr frts::EntityGroupSatelliteImpl::getComponentType() const
{
    return componentType;
}

frts::EntityPtr frts::EntityGroupSatelliteImpl::getMaster() const
{
    return master.lock();
}
