#include "MovableBuilder.h"

#include "MovableImpl.h"
#include <entity/ComponentIds.h>


frts::MovableBuilder::MovableBuilder()
{
}

frts::ComponentPtr frts::MovableBuilder::build(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto id = shared->makeId(ComponentIds::movable());
    return makeMovable(id);
}

frts::ComponentPtr frts::MovableBuilder::build(SharedManagerPtr shared, ConfigNodePtr)
{
    assert(shared != nullptr);

    // No config.
    return build(shared);
}
