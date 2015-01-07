#include "JobHandler.h"

#ifndef UNIT_TEST
#include "JobIds.h"
#include <frts/vanillaevent>
#include <frts/vanillamodel>
#endif


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

    // Only add if not already added.
    if (knownJobs.find(job) != knownJobs.end())
    {
        return;
    }

    // Start immediatly aka next tick.
    knownJobs.insert(job);
    runningJobs.push(std::make_pair(fromMilliseconds(0), job));
}

void frts::JobHandler::stopJob(JobPtr job)
{
    assert(job != nullptr);

    // Only stop if previously added.
    if (knownJobs.find(job) == knownJobs.end())
    {
        return;
    }

    toStop.insert(job);
}

void frts::JobHandler::tick(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto time = shared->getFrame()->getRunTime();

    // Running
    while(!runningJobs.empty() && runningJobs.top().first <= time)
    {
        auto tj = runningJobs.top();
        runningJobs.pop();

        // Is this job marked for stopping?
        auto it = toStop.find(tj.second);
        if (it != toStop.end())
        {
            toStop.erase(it);
            stoppingJobs.push(tj);
        }
        else
        {
            auto state = tj.second->execute(shared);

            // Is this job finished?
            if (state == Job::State::Finished)
            {
                knownJobs.erase(tj.second);

                #ifndef UNIT_TEST
                // Raise event.
                auto em = getUtility<EventManager>(shared, EventIds::eventManager());
                auto event = em->makeEvent(shared->makeId(JobIds::jobFinishedEvent()), shared);
                auto eventValue = makeEventValue<EntityEventValue>(em, ModelEventIds::entityEventValue(), shared);
                eventValue->setValue(tj.second->getExecutingEntity());
                event->setValue(shared->makeId(JobIds::entityEventValue()), eventValue);
                em->raise(event, shared);
                #endif
            }
            // Does this job want to cancel?
            else if (state == Job::State::Cancel)
            {
                stoppingJobs.push(tj);
            }
            // Another round.
            else
            {
                tj.first = tj.second->getDueTime();
                runningJobs.push(tj);
            }
        }
    }

    // Stopping
    while(!stoppingJobs.empty() && stoppingJobs.top().first <= time)
    {
        auto tj = stoppingJobs.top();
        stoppingJobs.pop();

        // Check if it is again in the stop list. Can happen.
        auto it = toStop.find(tj.second);
        if (it != toStop.end())
        {
            toStop.erase(it);
        }

        auto state = tj.second->stop(shared);

        // Another round.
        if (state == Job::State::Running)
        {
            tj.first = tj.second->getDueTime();
            stoppingJobs.push(tj);
        }
        // Job is finished.
        else
        {
            knownJobs.erase(tj.second);

            #ifndef UNIT_TEST
            // Raise event.
            auto em = getUtility<EventManager>(shared, EventIds::eventManager());
            auto event = em->makeEvent(shared->makeId(JobIds::jobStoppedEvent()), shared);
            auto eventValue = makeEventValue<EntityEventValue>(em, ModelEventIds::entityEventValue(), shared);
            eventValue->setValue(tj.second->getExecutingEntity());
            event->setValue(shared->makeId(JobIds::entityEventValue()), eventValue);
            em->raise(event, shared);
            #endif
        }
    }
}
