#include "TeleportBuilder.h"

#include "TeleportImpl.h"
#include <entity/ComponentIds.h>


frts::TeleportBuilder::TeleportBuilder()
{
}

frts::ComponentPtr frts::TeleportBuilder::build(SharedManagerPtr shared)
{
    auto id = shared->makeId(ComponentIds::teleport());
    return makeTeleport(id);
}

frts::ComponentPtr frts::TeleportBuilder::build(SharedManagerPtr shared, ConfigNodePtr)
{
    // No config.
    return build(shared);
}
