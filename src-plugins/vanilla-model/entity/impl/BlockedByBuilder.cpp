#include "BlockedByBuilder.h"

#include "BlockedByImpl.h"
#include <entity/ComponentIds.h>


frts::BlockedByBuilder::BlockedByBuilder()
{
}

frts::ComponentPtr frts::BlockedByBuilder::build(SharedManagerPtr shared)
{
    IdPtr id = shared->makeId(ComponentIds::blockedBy());
    return makeBlockedBy(id);
}

frts::ComponentPtr frts::BlockedByBuilder::build(SharedManagerPtr shared, ConfigNodePtr node)
{
    BlockedByPtr component = std::static_pointer_cast<BlockedBy>(build(shared));
    for (auto block : node->getStrings("blocks"))
    {
        IdPtr id = shared->makeId(block);
        component->addBlock(id);
    }
    return component;
}
