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

frts::ComponentPtr frts::MovableBuilder::build(SharedManagerPtr shared, ConfigNodePtr node)
{
    assert(shared != nullptr);
    assert(node != nullptr);

    auto component = std::static_pointer_cast<Movable>(build(shared));
    component->setSpeed(node->getInteger("speed"));
    return component;
}
