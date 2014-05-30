#include "IsResourceBuilder.h"

#include "IsResourceImpl.h"
#include <entity/ComponentIds.h>


frts::IsResourceBuilder::IsResourceBuilder()
{
}

frts::ComponentPtr frts::IsResourceBuilder::build(SharedManagerPtr shared)
{
    IdPtr id = shared->makeId(ComponentIds::isResource());
    return makeIsResource(id);
}
