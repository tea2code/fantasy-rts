#include "BlockingBuilder.h"

#include "BlockingImpl.h"
#include <entity/ComponentIds.h>


frts::BlockingBuilder::BlockingBuilder()
{
}

frts::ComponentPtr frts::BlockingBuilder::build(SharedManagerPtr shared)
{
    IdPtr id = shared->makeId(ComponentIds::blocking());
    return makeBlocking(id);
}

frts::ComponentPtr frts::BlockingBuilder::build(SharedManagerPtr shared, ConfigNodePtr node)
{
    BlockingPtr component = std::static_pointer_cast<Blocking>(build(shared));
    for (auto block : node->getStrings("blocks"))
    {
        IdPtr id = shared->makeId(block);
        component->addBlock(id);
    }
    return component;
}
