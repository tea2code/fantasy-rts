#include "HasResourceBuilder.h"

#include "HasResourceImpl.h"
#include <entity/ComponentIds.h>


frts::HasResourceBuilder::HasResourceBuilder(const std::string& resource)
    : resource{resource}
{
}

frts::ComponentPtr frts::HasResourceBuilder::build(SharedManagerPtr shared)
{
    IdPtr id = shared->makeId(ComponentIds::hasResource(resource));
    return makeHasResource(id);
}
