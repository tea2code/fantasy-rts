#include "SortOrderBuilder.h"

#include "SortOrderImpl.h"
#include <entity/ComponentIds.h>


frts::SortOrderBuilder::SortOrderBuilder()
{
}

frts::ComponentPtr frts::SortOrderBuilder::build(SharedManagerPtr shared)
{
    IdPtr id = shared->makeId(ComponentIds::sortOrder());
    return makeSortOrder(id);
}

frts::ComponentPtr frts::SortOrderBuilder::build(SharedManagerPtr shared, ConfigNodePtr node)
{
    SortOrderPtr component = std::static_pointer_cast<SortOrder>(build(shared));
    component->setSortOrder(node->getInteger("sort_order"));
    return component;
}
