#include "BlockedByBuilder.h"

#include "BlockedByImpl.h"
#include <entity/ComponentIds.h>


frts::BlockedByBuilder::BlockedByBuilder()
{
}

frts::ComponentPtr frts::BlockedByBuilder::build(const EntityPtr&, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto id = shared->makeId(ComponentIds::blockedBy());
    return makeBlockedBy(id);
}

frts::ComponentPtr frts::BlockedByBuilder::build(const EntityPtr& entity, const SharedManagerPtr& shared, const ConfigNodePtr& node)
{
    assert(entity != nullptr);
    assert(shared != nullptr);
    assert(node != nullptr);

    auto component = std::static_pointer_cast<BlockedBy>(build(entity, shared));
    for (auto& block : node->getStrings("blocks"))
    {
        auto id = shared->makeId(block);
        component->addBlock(id);
    }
    return component;
}
