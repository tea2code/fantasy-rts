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
