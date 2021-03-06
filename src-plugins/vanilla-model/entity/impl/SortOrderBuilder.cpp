#include "SortOrderBuilder.h"

#include "SortOrderImpl.h"
#include <entity/ComponentIds.h>


frts::SortOrderBuilder::SortOrderBuilder()
{
}

frts::ComponentPtr frts::SortOrderBuilder::build(const EntityPtr&, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto id = shared->makeId(ComponentIds::sortOrder());
    return makeSortOrder(id);
}

frts::ComponentPtr frts::SortOrderBuilder::build(const EntityPtr& entity, const SharedManagerPtr& shared, const ConfigNodePtr& node)
{
    assert(entity != nullptr);
    assert(shared != nullptr);
    assert(node != nullptr);

    auto component = std::static_pointer_cast<SortOrder>(build(entity, shared));
    component->setSortOrder(node->getInteger("sort_order"));
    return component;
}
