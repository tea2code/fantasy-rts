#include "BaseEntityImpl.h"


frts::BaseEntityImpl::BaseEntityImpl(BlockingPtr blockedBy, BlockingPtr blocking,
                                     IdPtr state, int sortOrder)
    : blockedBy{blockedBy}, blocking{blocking}, state{state}, sortOrder{sortOrder}
{
}

frts::BlockingPtr frts::BaseEntityImpl::getBlockedBy() const
{
    return blockedBy;
}

frts::BlockingPtr frts::BaseEntityImpl::getBlocking() const
{
    return blocking;
}

int frts::BaseEntityImpl::getSortOrder() const
{
    return sortOrder;
}

frts::IdPtr frts::BaseEntityImpl::getStateId() const
{
    return state;
}

void frts::BaseEntityImpl::setSortOrder(int sortOrder)
{
    this->sortOrder = sortOrder;
}

void frts::BaseEntityImpl::setStateId(IdPtr state)
{
    this->state = state;
}
