#include "BlockImpl.h"

#include <algorithm>
#include <iterator>


frts::BlockImpl::BlockImpl(IdPtr blockingType, IdPtr sortOrderType)
    : blockingType{blockingType}
{
    entities = std::unique_ptr<EntitySet>(new EntitySet(SortOrder::SortOrdered(sortOrderType)));
}

std::vector<frts::EntityPtr> frts::BlockImpl::getByComponent(IdPtr componentType) const
{
    std::vector<EntityPtr> result;
    std::copy_if(entities->begin(), entities->end(),
                 std::back_inserter(result),
                 HasComponentPred(componentType));
    return result;
}

bool frts::BlockImpl::has(EntityPtr entity) const
{
    auto itPair = entities->equal_range(entity);
    return (std::find(itPair.first, itPair.second, entity) != itPair.second);
}

void frts::BlockImpl::insert(EntityPtr entity)
{
    entities->insert(entity);
}

bool frts::BlockImpl::isBlocking(BlockedByPtr blockedBy) const
{
    return std::any_of(entities->begin(), entities->end(), IsBlockingPred(blockingType, blockedBy));
}

void frts::BlockImpl::remove(EntityPtr entity)
{
    auto itPair = entities->equal_range(entity);
    for (auto it = itPair.first; it != itPair.second; ++it)
    {
        if (*it == entity)
        {
            entities->erase(it);
        }
    }
}
