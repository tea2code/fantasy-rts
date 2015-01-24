#include "EntityGroupImpl.h"


frts::EntityGroupImpl::EntityGroupImpl(const IdPtr& componentType, const EntityVector& satellites, const EntityPosMap& positions)
    : componentType{componentType}, satellites{satellites}, positions{positions}
{
    for (auto entity : satellites)
    {
        assert(positions.find(entity) != positions.end());
    }
}

frts::EntityGroupImpl::~EntityGroupImpl()
{

}

frts::IdPtr frts::EntityGroupImpl::getComponentType() const
{
    return componentType;
}

frts::EntityVector frts::EntityGroupImpl::getSatellites() const
{
    return satellites;
}

frts::PointPtr frts::EntityGroupImpl::getSatellitePos(const EntityPtr& satellite) const
{
    assert(satellite != nullptr);

    return positions.at(satellite);
}
