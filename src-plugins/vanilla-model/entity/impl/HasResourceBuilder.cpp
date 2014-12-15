#include "HasResourceBuilder.h"

#include "HasResourceImpl.h"
#include <entity/ComponentIds.h>


frts::HasResourceBuilder::HasResourceBuilder()
{
}

frts::ComponentPtr frts::HasResourceBuilder::build(SharedManagerPtr shared)
{
    auto id = shared->makeId(ComponentIds::hasResource());
    return makeHasResource(id);
}

frts::ComponentPtr frts::HasResourceBuilder::build(SharedManagerPtr shared, ConfigNodePtr node)
{
    auto component = std::static_pointer_cast<HasResource>(build(shared));
    for (auto& resource : node->getStrings("resources"))
    {
        auto id = shared->makeId(resource);
        component->addResource(id);
    }
    return component;
}
