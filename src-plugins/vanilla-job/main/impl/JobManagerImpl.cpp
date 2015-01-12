#include "JobManagerImpl.h"

#include "JobMarkerBuilder.h"
#include <main/JobIds.h>

#include <frts/vanillaevent>
#include <frts/vanillamodel>

#include <algorithm>


frts::JobManagerImpl::JobManagerImpl(JobHandlerPtr jobHandler)
    : jobHandler{jobHandler}
{

}

frts::JobManagerImpl::~JobManagerImpl()
{

}

void frts::JobManagerImpl::addJob(JobPtr job)
{
    assert(job != nullptr);

    // Every job instance may only be added once.
    if (std::find(jobs.begin(), jobs.end(), job) == jobs.end())
    {
        jobs.push_back(job);
    }
}

void frts::JobManagerImpl::checkRequiredData(SharedManagerPtr)
{

}

bool frts::JobManagerImpl::createData(SharedManagerPtr)
{
    return false;
}

bool frts::JobManagerImpl::employEntity(EntityPtr entity, SharedManagerPtr shared)
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

std::string frts::JobManagerImpl::getName() const
{
    return JobIds::jobManager();
}

std::vector<std::string> frts::JobManagerImpl::getSupportedConfig()
{
    return {};
}

std::string frts::JobManagerImpl::getTypeName() const
{
    return getName();
}

int frts::JobManagerImpl::getTypeVersion() const
{
    return getVersion();
}

int frts::JobManagerImpl::getVersion() const
{
    return 2;
}

bool frts::JobManagerImpl::init(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    auto componentId = shared->makeId(JobIds::jobMarker());
    auto builder = makeJobMarkerBuilder();
    mf->registerComponentBuilder(componentId, builder);

    isInit = true;
    return false;
}

bool frts::JobManagerImpl::isInitialized() const
{
    return isInit;
}

bool frts::JobManagerImpl::isPreInitialized() const
{
    return isPreInit;
}

void frts::JobManagerImpl::parseConfig(const std::string&, ConfigNodePtr, SharedManagerPtr)
{

}

bool frts::JobManagerImpl::preInit(SharedManagerPtr)
{
    isPreInit = true;
    return false;
}

void frts::JobManagerImpl::stopJob(JobPtr job)
{
    assert(job != nullptr);

    auto it = std::find(jobs.begin(), jobs.end(), job);
    if (it != jobs.end())
    {
        // Not yet started.
        jobs.erase(it);
    }
    else
    {
        // May already be running.
        jobHandler->stopJob(job);
    }
}

void frts::JobManagerImpl::validateData(SharedManagerPtr)
{

}

void frts::JobManagerImpl::validateModules(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateTickable(getName(), JobIds::jobHandler(), 1, shared);
    validateUtility(getName(), EventIds::eventManager(), 1, shared);
}
