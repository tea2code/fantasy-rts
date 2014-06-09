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
