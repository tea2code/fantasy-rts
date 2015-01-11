#include "HarvestAction.h"

#include <frts/vanillasdl2input>


frts::HarvestAction::HarvestAction(IdUnorderedSet harvestTypes, IdUnorderedSet jobRequirements)
    : harvestTypes{harvestTypes}, jobRequirements{jobRequirements}
{

}

frts::HarvestAction::~HarvestAction()
{

}

frts::Action::State frts::HarvestAction::execute(SharedManagerPtr shared)
{
    assert(shared != nullptr);
    assert(this->harvestState != HarvestActionState::Finished);

    shared->getLog()->debug(name, "execute");

    State result = State::Running;

    // First execution. Wait for selection.
    if (harvestState == HarvestActionState::FirstExecution)
    {
        harvestState = HarvestActionState::WaitingForSelection;

        auto em = getUtility<EventManager>(shared, EventIds::eventManager());
        em->subscribe(shared_from_this(), shared->makeId(Sdl2Ids::selectionFinishedEvent()));
    }
    // Selection received. Add jobs.
    else if (harvestState == HarvestActionState::SelectionReceived)
    {
        shared->getLog()->debug(name, "execute->addingJobs");

        harvestState = HarvestActionState::Finished;
        result = State::Finished;

        // TODO Add jobs to job manager.
        // TODO Add job entities to positions.
    }
    // Action was previously stopped but the action manager doesn't know yet.
    else if (harvestState == HarvestActionState::Stopped)
    {
        result = State::Cancel;
    }

    return result;
}

void frts::HarvestAction::notify(EventPtr event, SharedManagerPtr shared)
{
    assert(event != nullptr);
    assert(shared != nullptr);

    shared->getLog()->debug(name, "notify");

    // Selection complete.
    harvestState = HarvestActionState::SelectionReceived;

    auto value = getEventValue<PointListEventValue>(event, shared->makeId(Sdl2Ids::selectionEventValue()));
    selection = value->getValue();

    // Unsubscribe from selection events.
    auto em = getUtility<EventManager>(shared, EventIds::eventManager());
    em->unsubscribe(shared_from_this());
}

frts::Action::State frts::HarvestAction::stop(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    shared->getLog()->debug(name, "stop");

    // Stop waiting for selection.
    if (harvestState == HarvestActionState::WaitingForSelection)
    {
        auto em = getUtility<EventManager>(shared, EventIds::eventManager());
        em->unsubscribe(shared_from_this());
    }
    // Stop/Cancel jobs.
    else if (harvestState == HarvestActionState::Finished)
    {
        shared->getLog()->debug(name, "execute->stoppingJobs");

        // Stop/Cancel jobs.
        auto jm = getUtility<JobManager>(shared, JobIds::jobManager());
        for (auto job : jobs)
        {
            jm->stopJob(job);
        }

        // Remove job entities.
        auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
        for (auto jobEntity : jobEntities)
        {
            rm->removeEntity(jobEntity, shared);
        }
    }

    harvestState = HarvestActionState::Stopped;
    return State::Finished;
}
