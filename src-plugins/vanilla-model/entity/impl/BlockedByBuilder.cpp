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
