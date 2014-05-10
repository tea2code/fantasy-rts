#include "DynamicEntityImpl.h"


frts::DynamicEntityImpl::DynamicEntityImpl(BlockingPtr blockedBy, BlockingPtr blocking,
                                           IdPtr state, int sortOrder)
    : baseEntity{blockedBy, blocking, state, sortOrder}
{

}

frts::BlockingPtr frts::DynamicEntityImpl::getBlockedBy() const
{
    return baseEntity.getBlockedBy();
}

frts::BlockingPtr frts::DynamicEntityImpl::getBlocking() const
{
    return baseEntity.getBlocking();
}

int frts::DynamicEntityImpl::getSortOrder() const
{
    return baseEntity.getSortOrder();
}

frts::IdPtr frts::DynamicEntityImpl::getStateId() const
{
    return baseEntity.getStateId();
}

frts::Entity::Type frts::DynamicEntityImpl::getType() const
{
    return Type::Dynamic;
}

void frts::DynamicEntityImpl::setSortOrder(int sortOrder)
{
    baseEntity.setSortOrder(sortOrder);
}

void frts::DynamicEntityImpl::setStateId(IdPtr state)
{
    baseEntity.setStateId(state);
}

