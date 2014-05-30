#include "HasResourceBuilder.h"

#include "HasResourceImpl.h"
#include <entity/ComponentIds.h>


frts::HasResourceBuilder::HasResourceBuilder()
{
}

frts::ComponentPtr frts::HasResourceBuilder::build(SharedManagerPtr shared)
{
    IdPtr id = shared->makeId(ComponentIds::hasResource());
    return makeHasResource(id);
}
