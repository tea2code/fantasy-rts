#include "MovableBuilder.h"

#include "MovableImpl.h"
#include <entity/ComponentIds.h>


frts::MovableBuilder::MovableBuilder()
{
}

frts::ComponentPtr frts::MovableBuilder::build(SharedManagerPtr shared)
{
    auto id = shared->makeId(ComponentIds::movable());
    return makeMovable(id);
}

frts::ComponentPtr frts::MovableBuilder::build(SharedManagerPtr shared, ConfigNodePtr)
{
    // No config.
    return build(shared);
}