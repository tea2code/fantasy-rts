#include "IsResourceBuilder.h"

#include "IsResourceImpl.h"
#include <entity/ComponentIds.h>


frts::IsResourceBuilder::IsResourceBuilder()
{
}

frts::ComponentPtr frts::IsResourceBuilder::build(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto id = shared->makeId(ComponentIds::isResource());
    return makeIsResource(id);
}

frts::ComponentPtr frts::IsResourceBuilder::build(SharedManagerPtr shared, ConfigNodePtr node)
{
    assert(shared != nullptr);
    assert(node != nullptr);

    auto component = std::static_pointer_cast<IsResource>(build(shared));
    auto id = shared->makeId(node->getString("resource_type"));
    component->setResourceType(id);
    return component;
}
