#include "DropBuilder.h"

#include "DropImpl.h"
#include <entity/ComponentIds.h>


frts::DropBuilder::DropBuilder()
{
}

frts::ComponentPtr frts::DropBuilder::build(SharedManagerPtr shared)
{
    auto id = shared->makeId(ComponentIds::drop());
    return makeDrop(id);
}

frts::ComponentPtr frts::DropBuilder::build(SharedManagerPtr shared, ConfigNodePtr node)
{
    auto component = std::static_pointer_cast<Drop>(build(shared));
    for (auto& drop : node->getStrings("drops"))
    {
        auto id = shared->makeId(drop);
        component->addDrop(id);
    }
    return component;
}
