#include "EntityGroupImpl.h"


frts::EntityGroupImpl::EntityGroupImpl(IdPtr componentType, EntityVector satellites, EntityPosMap positions)
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

frts::PointPtr frts::EntityGroupImpl::getSatellitePos(EntityPtr satellite) const
{
    assert(satellite != nullptr);

    return positions.at(satellite);
}
