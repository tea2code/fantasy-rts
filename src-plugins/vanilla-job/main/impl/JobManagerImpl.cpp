#include "JobManagerImpl.h"

#include <main/JobIds.h>

#include <frts/vanillaevent>


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

    // TODO
}

void frts::JobManagerImpl::checkRequiredData(SharedManagerPtr)
{

}

bool frts::JobManagerImpl::createData(SharedManagerPtr)
{
    return false;
}

bool frts::JobManagerImpl::employEntity(EntityPtr entity)
{
    assert(entity != nullptr);

    // TODO

    return false;
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
    return 1;
}

bool frts::JobManagerImpl::init(SharedManagerPtr)
{
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

    // TODO
}

void frts::JobManagerImpl::validateData(SharedManagerPtr)
{

}

void frts::JobManagerImpl::validateModules(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateTickable(getName(), "frts::JobHandler", 1, shared);
    validateUtility(getName(), EventIds::eventManager(), 1, shared);
}
