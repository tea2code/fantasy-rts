#include "HarvestAction.h"

#include "HarvestJob.h"

#include <frts/vanillasdl2input>

#include <algorithm>


frts::HarvestAction::HarvestAction(IdUnorderedSet harvestTypes, IdUnorderedSet jobRequirements, IdPtr jobMarker)
    : harvestTypes{harvestTypes}, jobRequirements{jobRequirements}, jobMarker{jobMarker}
{

}

frts::HarvestAction::~HarvestAction()
{

}

frts::Action::State frts::HarvestAction::execute(SharedManagerPtr shared)
{
    assert(shared != nullptr);
    assert(this->harvestState != HarvestActionState::Finished);

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

        // Add jobs to job manager and job markers to region.
        auto jm = getUtility<JobManager>(shared, JobIds::jobManager());
        auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
        auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
        auto harvestableId = shared->makeId(ComponentIds::harvestable());
        auto jobMarkerId = shared->makeId(JobIds::jobMarker());
        for (auto& pos : selection)
        {
            auto block = rm->getBlock(pos, shared);
            auto entities = block->getByComponent(harvestableId);
            for (auto entity : entities)
            {
                // Any supported harvestable type?
                auto harvestable = getComponent<Harvestable>(harvestableId, entity);
                bool toHarvest = std::any_of(harvestTypes.begin(), harvestTypes.end(),
                                             [&](IdPtr type) { return harvestable->hasType(type); });
                if (!toHarvest)
                {
                    continue;
                }

                // Add job for this entity.
                auto jobMarkerEntity = mf->makeEntity(jobMarker, shared);
                auto job = makeHarvestJob(entity, jobRequirements, jobMarkerEntity);
                jm->addJob(job, shared);
                jobs.push_back(job);

                // Add job marker at this position.
                auto jobMarkerComponent = getComponent<JobMarker>(jobMarkerId, jobMarkerEntity);
                jobMarkerComponent->setJob(job);
                rm->setPos(jobMarkerEntity, pos, shared);
                jobEntities.push_back(jobMarkerEntity);
            }
        }
        selection.clear();
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

    // Stop waiting for selection.
    if (harvestState == HarvestActionState::WaitingForSelection)
    {
        auto em = getUtility<EventManager>(shared, EventIds::eventManager());
        em->unsubscribe(shared_from_this());
    }
    // Stop/Cancel jobs.
    else if (harvestState == HarvestActionState::Finished)
    {
        // Stop/Cancel jobs.
        auto jm = getUtility<JobManager>(shared, JobIds::jobManager());
        for (auto job : jobs)
        {
            jm->stopJob(job, shared);
        }
        jobs.clear();

        // Remove job entities.
        auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
        for (auto jobEntity : jobEntities)
        {
            rm->removeEntity(jobEntity, shared);
        }
        jobEntities.clear();
    }

    harvestState = HarvestActionState::Stopped;
    return State::Finished;
}
