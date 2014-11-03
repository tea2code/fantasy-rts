#include "BlockedByBuilder.h"

#include "BlockedByImpl.h"
#include <entity/ComponentIds.h>


frts::BlockedByBuilder::BlockedByBuilder()
{
}

frts::ComponentPtr frts::BlockedByBuilder::build(SharedManagerPtr shared)
{
    auto id = shared->makeId(ComponentIds::blockedBy());
    return makeBlockedBy(id);
}

frts::ComponentPtr frts::BlockedByBuilder::build(SharedManagerPtr shared, ConfigNodePtr node)
{
    auto component = std::static_pointer_cast<BlockedBy>(build(shared));
    for (auto block : node->getStrings("blocks"))
    {
        auto id = shared->makeId(block);
        component->addBlock(id);
    }
    return component;
}
