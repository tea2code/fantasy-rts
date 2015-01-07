#include "JobHandler.h"

#include "JobIds.h"
#include "JobManager.h"

#ifndef UNIT_TEST
#include "JobIds.h"
#include <frts/vanillaevent>
#include <frts/vanillamodel>
#endif


namespace
{
    #ifndef UNIT_TEST
    void raiseEvent(const std::string& eventId, frts::EntityPtr entity, frts::SharedManagerPtr shared)
    {
        auto em = frts::getUtility<frts::EventManager>(shared, frts::EventIds::eventManager());
        auto event = em->makeEvent(shared->makeId(eventId), shared);
        auto eventValue = frts::makeEventValue<frts::EntityEventValue>(em, frts::ModelEventIds::entityEventValue(), shared);
        eventValue->setValue(entity);
        event->setValue(shared->makeId(frts::JobIds::entityEventValue()), eventValue);
        em->raise(event, shared);
    }
    #else
    void raiseEvent(const std::string&, frts::EntityPtr, frts::SharedManagerPtr)
    {
        // Dummy
    }
    #endif
}

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
                raiseEvent(JobIds::jobFinishedEvent(), tj.second->getExecutingEntity(), shared);
            }
            // Does this job want to cancel?
            else if (state == Job::State::Cancel)
            {
                // Execution cancelt. Send it back to the job manager.
                tj.second->setExecutingEntity(nullptr);
                auto jm = getUtility<JobManager>(shared, JobIds::jobManager());
                jm->addJob(tj.second);

                raiseEvent(JobIds::jobCanceledEvent(), tj.second->getExecutingEntity(), shared);
            }
            // Does this job want to stop completely?
            else if (state == Job::State::Stop)
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
            raiseEvent(JobIds::jobStoppedEvent(), tj.second->getExecutingEntity(), shared);
        }
    }
}
