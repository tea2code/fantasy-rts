#include "MovableBuilder.h"

#include "MovableImpl.h"
#include <entity/ComponentIds.h>

#include <frts/module>


frts::MovableBuilder::MovableBuilder()
{
}

frts::ComponentPtr frts::MovableBuilder::build(const EntityPtr&, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto id = shared->makeId(ComponentIds::movable());
    return makeMovable(id);
}

frts::ComponentPtr frts::MovableBuilder::build(const EntityPtr& entity, const SharedManagerPtr& shared, const ConfigNodePtr& node)
{
    assert(entity != nullptr);
    assert(shared != nullptr);
    assert(node != nullptr);

    auto component = std::static_pointer_cast<Movable>(build(entity, shared));
    component->setSpeed(node->getFloat("speed"));
    if (!(component->getSpeed() > 0.0))
    {
        throw DataViolation("frts::MovableBuilder: Speed of movable must be greater than zero.");
    }
    return component;
}
