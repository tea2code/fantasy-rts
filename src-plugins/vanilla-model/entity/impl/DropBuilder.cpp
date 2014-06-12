#include "DropBuilder.h"

#include "DropImpl.h"
#include <entity/ComponentIds.h>


frts::DropBuilder::DropBuilder()
{
}

frts::ComponentPtr frts::DropBuilder::build(SharedManagerPtr shared)
{
    IdPtr id = shared->makeId(ComponentIds::drop());
    return makeDrop(id);
}

frts::ComponentPtr frts::DropBuilder::build(SharedManagerPtr shared, ConfigNodePtr node)
{
    DropPtr component = std::static_pointer_cast<Drop>(build(shared));
    for (auto drop : node->getStrings("drops"))
    {
        IdPtr id = shared->makeId(drop);
        component->addDrop(id);
    }
    return component;
}
