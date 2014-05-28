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
