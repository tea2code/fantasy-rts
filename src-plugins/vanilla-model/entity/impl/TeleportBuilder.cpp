#include "TeleportBuilder.h"

#include "TeleportImpl.h"
#include <entity/ComponentIds.h>


frts::TeleportBuilder::TeleportBuilder()
{
}

frts::ComponentPtr frts::TeleportBuilder::build(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto id = shared->makeId(ComponentIds::teleport());
    return makeTeleport(id);
}

frts::ComponentPtr frts::TeleportBuilder::build(const SharedManagerPtr& shared, const ConfigNodePtr&)
{
    assert(shared != nullptr);

    // No config.
    return build(shared);
}
