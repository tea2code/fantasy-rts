#include "JobHandler.h"


frts::JobHandler::JobHandler()
    : BaseTickable("frts::JobHandler", 1, "frts::JobHandler", 1)
{

}

frts::JobHandler::~JobHandler()
{

}

void frts::JobHandler::runJob(JobPtr job)
{
    assert(job != nullptr);

    // TODO
}

void frts::JobHandler::stopJob(JobPtr job)
{
    assert(job != nullptr);

    // TODO
}

void frts::JobHandler::tick(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    // TODO

#ifndef UNIT_TEST
    // TODO Send events here.
#endif
}
