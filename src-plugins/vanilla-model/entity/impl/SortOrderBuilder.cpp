#include "SortOrderBuilder.h"

#include "SortOrderImpl.h"
#include <entity/ComponentIds.h>


frts::SortOrderBuilder::SortOrderBuilder()
{
}

frts::ComponentPtr frts::SortOrderBuilder::build(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto id = shared->makeId(ComponentIds::sortOrder());
    return makeSortOrder(id);
}

frts::ComponentPtr frts::SortOrderBuilder::build(SharedManagerPtr shared, ConfigNodePtr node)
{
    assert(shared != nullptr);
    assert(node != nullptr);

    auto component = std::static_pointer_cast<SortOrder>(build(shared));
    component->setSortOrder(node->getInteger("sort_order"));
    return component;
}
