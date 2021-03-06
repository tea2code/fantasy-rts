#include "JobMarkerBuilder.h"

#include "JobMarkerImpl.h"
#include <main/JobIds.h>


frts::JobMarkerBuilder::JobMarkerBuilder()
{

}

frts::JobMarkerBuilder::~JobMarkerBuilder()
{

}

frts::ComponentPtr frts::JobMarkerBuilder::build(const EntityPtr&, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    return makeJobMarker(shared->makeId(JobIds::jobMarker()));
}

frts::ComponentPtr frts::JobMarkerBuilder::build(const EntityPtr& entity, const SharedManagerPtr& shared, const ConfigNodePtr&)
{
    assert(entity != nullptr);
    assert(shared != nullptr);

    // No config.
    return build(entity, shared);
}
