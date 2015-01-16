#include "DropImpl.h"

#include <algorithm>


frts::DropImpl::DropImpl(const IdPtr& type)
    : type{type}
{
}

void frts::DropImpl::addDrop(const IdPtr& entityId)
{
    assert(entityId != nullptr);

    drops.push_back(entityId);
}

frts::IdPtr frts::DropImpl::getComponentType() const
{
    return type;
}

std::vector<frts::IdPtr> frts::DropImpl::getDrops() const
{
    return drops;
}

bool frts::DropImpl::hasDrop(const IdPtr& entityId) const
{
    assert(entityId != nullptr);

    auto it = std::find_if(drops.begin(), drops.end(), IdComparison(entityId));
    return it != drops.end();
}

void frts::DropImpl::removeDrop(const IdPtr& entityId)
{
    assert(entityId != nullptr);

    auto it = std::find_if(drops.begin(), drops.end(), IdComparison(entityId));
    if (it == drops.end())
    {
        return;
    }
    drops.erase(it);
}
