#include "BlockingBuilder.h"

#include "BlockingImpl.h"
#include <entity/ComponentIds.h>


frts::BlockingBuilder::BlockingBuilder()
{
}

frts::ComponentPtr frts::BlockingBuilder::build(const EntityPtr&, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto id = shared->makeId(ComponentIds::blocking());
    return makeBlocking(id);
}

frts::ComponentPtr frts::BlockingBuilder::build(const EntityPtr& entity, const SharedManagerPtr& shared, const ConfigNodePtr& node)
{
    assert(entity != nullptr);
    assert(shared != nullptr);
    assert(node != nullptr);

    auto component = std::static_pointer_cast<Blocking>(build(entity, shared));
    for (auto& block : node->getStrings("blocks"))
    {
        auto id = shared->makeId(block);
        component->addBlock(id);
    }
    return component;
}
