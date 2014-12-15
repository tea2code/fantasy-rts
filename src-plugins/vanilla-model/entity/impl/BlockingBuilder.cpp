#include "BlockingBuilder.h"

#include "BlockingImpl.h"
#include <entity/ComponentIds.h>


frts::BlockingBuilder::BlockingBuilder()
{
}

frts::ComponentPtr frts::BlockingBuilder::build(SharedManagerPtr shared)
{
    auto id = shared->makeId(ComponentIds::blocking());
    return makeBlocking(id);
}

frts::ComponentPtr frts::BlockingBuilder::build(SharedManagerPtr shared, ConfigNodePtr node)
{
    auto component = std::static_pointer_cast<Blocking>(build(shared));
    for (auto& block : node->getStrings("blocks"))
    {
        auto id = shared->makeId(block);
        component->addBlock(id);
    }
    return component;
}
