#include "TileImpl.h"


frts::TileImpl::TileImpl(BlockingPtr blockedBy, BlockingPtr blocking,
                         IdPtr state, int sortOrder)
    : baseEntity{blockedBy, blocking, state, sortOrder}
{

}

frts::BlockingPtr frts::TileImpl::getBlockedBy() const
{
    return baseEntity.getBlockedBy();
}

frts::BlockingPtr frts::TileImpl::getBlocking() const
{
    return baseEntity.getBlocking();
}

int frts::TileImpl::getSortOrder() const
{
    return baseEntity.getSortOrder();
}

frts::IdPtr frts::TileImpl::getStateId() const
{
    return baseEntity.getStateId();
}

frts::Entity::Type frts::TileImpl::getType() const
{
    return Type::Dynamic;
}

void frts::TileImpl::setSortOrder(int sortOrder)
{
    baseEntity.setSortOrder(sortOrder);
}

void frts::TileImpl::setStateId(IdPtr state)
{
    baseEntity.setStateId(state);
}

