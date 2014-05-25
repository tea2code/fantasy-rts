#include "BlockImpl.h"

#include <algorithm>


frts::BlockImpl::BlockImpl(IdPtr blockingType, IdPtr sortOrderType)
    : blockingType{blockingType}, entities{SortOrder::SortOrdered(sortOrderType)}
{
}

frts::Block::EntitySet frts::BlockImpl::getByComponent(IdPtr componentType) const
{
    auto it = std::find_if(entities.begin(), entities.end(), HasComponentPred(componentType));
    return EntitySet(it, entities.end());
    return entities;
}

bool frts::BlockImpl::has(EntityPtr entity) const
{
    auto itPair = entities.equal_range(entity);
    return (std::find(itPair.first, itPair.second, entity) != itPair.second);
}

void frts::BlockImpl::insert(EntityPtr entity)
{
    entities.insert(entity);
}

bool frts::BlockImpl::isBlocking(BlockedByPtr blockedBy) const
{
    return std::any_of(entities.begin(), entities.end(), IsBlockingPred(blockingType, blockedBy));
}

void frts::BlockImpl::remove(EntityPtr entity)
{
    entities.erase(entity);
}
