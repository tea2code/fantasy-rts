#include "TeleportBuilder.h"

#include "TeleportImpl.h"
#include <entity/ComponentIds.h>


frts::TeleportBuilder::TeleportBuilder()
{
}

frts::ComponentPtr frts::TeleportBuilder::build(const EntityPtr&, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto id = shared->makeId(ComponentIds::teleport());
    return makeTeleport(id);
}

frts::ComponentPtr frts::TeleportBuilder::build(const EntityPtr& entity, const SharedManagerPtr& shared, const ConfigNodePtr&)
{
    assert(entity != nullptr);
    assert(shared != nullptr);

    // No config.
    return build(entity, shared);
}
