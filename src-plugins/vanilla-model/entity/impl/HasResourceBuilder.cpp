#include "HasResourceBuilder.h"

#include "HasResourceImpl.h"
#include <entity/ComponentIds.h>


frts::HasResourceBuilder::HasResourceBuilder()
{
}

frts::ComponentPtr frts::HasResourceBuilder::build(const EntityPtr&, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto id = shared->makeId(ComponentIds::hasResource());
    return makeHasResource(id);
}

frts::ComponentPtr frts::HasResourceBuilder::build(const EntityPtr& entity, const SharedManagerPtr& shared, const ConfigNodePtr& node)
{
    assert(entity != nullptr);
    assert(shared != nullptr);
    assert(node != nullptr);

    auto component = std::static_pointer_cast<HasResource>(build(entity, shared));
    for (auto& resource : node->getStrings("resources"))
    {
        auto id = shared->makeId(resource);
        component->addResource(id);
    }
    return component;
}
