#include "IsResourceBuilder.h"

#include "IsResourceImpl.h"
#include <entity/ComponentIds.h>


frts::IsResourceBuilder::IsResourceBuilder(const std::string& resource)
    : resource{resource}
{
}

frts::ComponentPtr frts::IsResourceBuilder::build(SharedManagerPtr shared)
{
    IdPtr id = shared->makeId(ComponentIds::isResource(resource));
    return makeIsResource(id);
}
