#include "TeleportBuilder.h"

#include "TeleportImpl.h"
#include <entity/ComponentIds.h>


frts::TeleportBuilder::TeleportBuilder()
{
}

frts::ComponentPtr frts::TeleportBuilder::build(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto id = shared->makeId(ComponentIds::teleport());
    return makeTeleport(id);
}

frts::ComponentPtr frts::TeleportBuilder::build(SharedManagerPtr shared, ConfigNodePtr)
{
    assert(shared != nullptr);

    // No config.
    return build(shared);
}
