#include "ResourceImpl.h"


frts::ResourceImpl::ResourceImpl(BlockingPtr blockedBy, BlockingPtr blocking,
                                 IdPtr state, int sortOrder)
    : baseEntity{blockedBy, blocking, state, sortOrder}
{

}

frts::BlockingPtr frts::ResourceImpl::getBlockedBy() const
{
    return baseEntity.getBlockedBy();
}

frts::BlockingPtr frts::ResourceImpl::getBlocking() const
{
    return baseEntity.getBlocking();
}

int frts::ResourceImpl::getSortOrder() const
{
    return baseEntity.getSortOrder();
}

frts::IdPtr frts::ResourceImpl::getStateId() const
{
    return baseEntity.getStateId();
}

frts::Entity::Type frts::ResourceImpl::getType() const
{
    return Type::Resource;
}

void frts::ResourceImpl::setSortOrder(int sortOrder)
{
    baseEntity.setSortOrder(sortOrder);
}

void frts::ResourceImpl::setStateId(IdPtr state)
{
    baseEntity.setStateId(state);
}

