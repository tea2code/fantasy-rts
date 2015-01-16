#include "StopJobsAction.h"

#include <frts/vanillajob>
#include <frts/vanillasdl2input>


frts::StopJobsAction::StopJobsAction(const IdUnorderedSet& jobs, const IdUnorderedSet& types)
    : jobs{jobs}, types{types}
{

}

frts::StopJobsAction::~StopJobsAction()
{

}

frts::Action::State frts::StopJobsAction::execute(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);
    assert(this->actionState != ActionState::Finished);

    State result = State::Running;

    // First execution. Wait for selection.
    if (actionState == ActionState::FirstExecution)
    {
        actionState = ActionState::WaitingForSelection;

        auto em = getUtility<EventManager>(shared, EventIds::eventManager());
        em->subscribe(shared_from_this(), shared->makeId(Sdl2Ids::selectionFinishedEvent()));
    }
    // Selection received. Add jobs.
    else if (actionState == ActionState::SelectionReceived)
    {
        actionState = ActionState::Finished;
        result = State::Finished;

        auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
        auto jm = getUtility<JobManager>(shared, JobIds::jobManager());

        for (auto& pos : selection)
        {
            auto block = rm->getBlock(pos, shared);
            auto jobMarkerId = shared->makeId(JobIds::jobMarker());
            auto joMarkers = block->getByComponent(jobMarkerId);
            for (auto& jobMarker : joMarkers)
            {
                auto marker = getComponent<JobMarker>(jobMarkerId, jobMarker);
                auto job = marker->getJob();

                // Filter
                if ((!jobs.empty() && jobs.find(job->getId()) == jobs.end()) ||
                    (!types.empty() && types.find(job->getType()) == types.end()))
                {
                    continue;
                }

                jm->stopJob(job, shared);
            }
        }
    }
    // Action was previously stopped but the action manager doesn't know yet.
    else if (actionState == ActionState::Stopped)
    {
        result = State::Cancel;
    }

    return result;
}

void frts::StopJobsAction::notify(const EventPtr& event, const SharedManagerPtr& shared)
{
    assert(event != nullptr);
    assert(shared != nullptr);

    // Selection complete.
    actionState = ActionState::SelectionReceived;

    auto value = getEventValue<PointListEventValue>(event, shared->makeId(Sdl2Ids::selectionEventValue()));
    selection = value->getValue();

    // Unsubscribe from selection events.
    auto em = getUtility<EventManager>(shared, EventIds::eventManager());
    em->unsubscribe(shared_from_this());
}

frts::Action::State frts::StopJobsAction::stop(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    // Stop waiting for selection.
    if (actionState == ActionState::WaitingForSelection)
    {
        auto em = getUtility<EventManager>(shared, EventIds::eventManager());
        em->unsubscribe(shared_from_this());
    }

    actionState = ActionState::Stopped;
    return State::Finished;
}
