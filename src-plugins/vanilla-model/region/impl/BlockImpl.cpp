#include "BlockImpl.h"

#include <algorithm>
#include <iterator>


frts::BlockImpl::BlockImpl(const IdPtr& blockingType, const IdPtr& sortOrderType)
    : blockingType{blockingType}
{
    entities = std::unique_ptr<EntitySet>(new EntitySet(SortOrder::SortOrdered(sortOrderType)));
}

std::vector<frts::EntityPtr> frts::BlockImpl::getByComponent(const IdPtr& componentType) const
{
    assert(componentType != nullptr);

    std::lock_guard<RecursiveLock> lock(locker);

    EntityVector result;
    std::copy_if(entities->begin(), entities->end(),
                 std::back_inserter(result),
                 HasComponentPred(componentType));
    return result;
}

std::vector<frts::EntityPtr> frts::BlockImpl::getEntities() const
{
    std::lock_guard<RecursiveLock> lock(locker);

    EntityVector result;
    std::copy(entities->begin(), entities->end(), std::back_inserter(result));
    return result;
}

bool frts::BlockImpl::has(const EntityPtr& entity) const
{
    assert(entity != nullptr);

    std::lock_guard<RecursiveLock> lock(locker);

    auto itPair = entities->equal_range(entity);
    return (std::find(itPair.first, itPair.second, entity) != itPair.second);
}

void frts::BlockImpl::insert(const EntityPtr& entity)
{
    assert(entity != nullptr);

    std::lock_guard<RecursiveLock> lock(locker);

    entities->insert(entity);
}

bool frts::BlockImpl::isBlocking(const BlockedByPtr& blockedBy) const
{
    if (blockedBy == nullptr)
    {
        return false;
    }

    std::lock_guard<RecursiveLock> lock(locker);

    return std::any_of(entities->begin(), entities->end(), IsBlockingPred(blockingType, blockedBy));
}

void frts::BlockImpl::remove(const EntityPtr& entity)
{
    assert(entity != nullptr);

    std::lock_guard<RecursiveLock> lock(locker);

    auto itPair = entities->equal_range(entity);
    for (auto it = itPair.first; it != itPair.second; ++it)
    {
        if (*it == entity)
        {
            entities->erase(it);
            break;
        }
    }
}
