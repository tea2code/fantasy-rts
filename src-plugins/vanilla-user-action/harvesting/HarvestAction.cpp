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
        harvestState = HarvestActionState::Finished;
        result = State::Finished;

        // TODO Add jobs to job manager.
        // TODO Add job entities to positions.
        shared->getLog()->debug(name, "execute->addingJobs");
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
        // TODO Stop/Cancel jobs.
        // TODO Remove job entities.
        shared->getLog()->debug(name, "execute->stoppingJobs");
    }

    harvestState = HarvestActionState::Stopped;
    return State::Finished;
}
