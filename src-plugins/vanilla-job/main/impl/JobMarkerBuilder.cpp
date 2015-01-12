#include "JobMarkerBuilder.h"

#include "JobMarkerImpl.h"
#include <main/JobIds.h>


frts::JobMarkerBuilder::JobMarkerBuilder()
{

}

frts::JobMarkerBuilder::~JobMarkerBuilder()
{

}

frts::ComponentPtr frts::JobMarkerBuilder::build(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    return makeJobMarker(shared->makeId(JobIds::jobMarker()));
}

frts::ComponentPtr frts::JobMarkerBuilder::build(SharedManagerPtr shared, ConfigNodePtr)
{
    assert(shared != nullptr);

    return build(shared);
}
