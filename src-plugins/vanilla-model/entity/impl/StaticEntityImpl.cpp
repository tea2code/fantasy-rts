#include "StaticEntityImpl.h"


frts::StaticEntityImpl::StaticEntityImpl(BlockingPtr blockedBy, BlockingPtr blocking,
                                         IdPtr state, int sortOrder)
    : baseEntity{blockedBy, blocking, state, sortOrder}
{

}

frts::BlockingPtr frts::StaticEntityImpl::getBlockedBy() const
{
    return baseEntity.getBlockedBy();
}

frts::BlockingPtr frts::StaticEntityImpl::getBlocking() const
{
    return baseEntity.getBlocking();
}

int frts::StaticEntityImpl::getSortOrder() const
{
    return baseEntity.getSortOrder();
}

frts::IdPtr frts::StaticEntityImpl::getStateId() const
{
    return baseEntity.getStateId();
}

frts::Entity::Type frts::StaticEntityImpl::getType() const
{
    return Type::Dynamic;
}

void frts::StaticEntityImpl::setSortOrder(int sortOrder)
{
    baseEntity.setSortOrder(sortOrder);
}

void frts::StaticEntityImpl::setStateId(IdPtr state)
{
    baseEntity.setStateId(state);
}

