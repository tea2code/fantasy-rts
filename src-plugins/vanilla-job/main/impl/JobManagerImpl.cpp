#include "JobManagerImpl.h"

#include "JobMarkerBuilder.h"
#include <main/JobIds.h>

#include <frts/vanillaevent>
#include <frts/vanillamodel>

#include <algorithm>


frts::JobManagerImpl::JobManagerImpl(const JobHandlerPtr& jobHandler)
    : BaseUtility(JobIds::jobManager(), 3, JobIds::jobManager(), 3),
      jobHandler{jobHandler}
{

}

frts::JobManagerImpl::~JobManagerImpl()
{

}

void frts::JobManagerImpl::addJob(const JobPtr& job, const SharedManagerPtr&)
{
    assert(job != nullptr);

    // Every job instance may only be added once.
    if (std::find(jobs.begin(), jobs.end(), job) == jobs.end())
    {
        jobs.push_back(job);
    }
}

bool frts::JobManagerImpl::employEntity(const EntityPtr& entity, const SharedManagerPtr& shared)
{
    assert(entity != nullptr);
    assert(shared != nullptr);

    bool result = false;

    auto curriculumId = shared->makeId(ComponentIds::curriculum());
    if (!entity->hasComponent(curriculumId))
    {
        shared->getLog()->warning(getName(), "Tried to employ an entity without curriculum.");
        return result;
    }
    auto curriculum = getComponent<Curriculum>(curriculumId, entity);

    auto hasAbility = [&](IdPtr ability)
    {
        return curriculum->hasAbility(ability);
    };
    auto satisfiesRequirements = [&](JobPtr job)
    {
        auto requirements = job->getRequirements();
        return std::all_of(requirements.begin(), requirements.end(), hasAbility) &&
               job->checkSpecialRequirements(entity, shared);
    };

    auto it = std::find_if(jobs.begin(), jobs.end(), satisfiesRequirements);
    if (it != jobs.end())
    {
        auto job = *it;
        jobs.erase(it);
        job->setExecutingEntity(entity);
        jobHandler->runJob(job);
        result = true;
    }

    return result;
}

bool frts::JobManagerImpl::init(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    auto componentId = shared->makeId(JobIds::jobMarker());
    auto builder = makeJobMarkerBuilder();
    mf->registerComponentBuilder(componentId, builder);

    return BaseUtility::init(shared);
}

void frts::JobManagerImpl::stopJob(const JobPtr& job, const SharedManagerPtr& shared)
{
    assert(job != nullptr);
    assert(shared != nullptr);

    auto it = std::find(jobs.begin(), jobs.end(), job);
    if (it != jobs.end())
    {
        // Not yet started.
        (*it)->stop(shared);
        jobs.erase(it);
    }
    else
    {
        // May already be running.
        jobHandler->stopJob(job);
    }
}

void frts::JobManagerImpl::validateModules(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    validateTickable(getName(), JobIds::jobHandler(), 1, shared);
    validateUtility(getName(), EventIds::eventManager(), 1, shared);
}
