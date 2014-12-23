#include "EventManagerImpl.h"

#include <main/EventIds.h>


frts::EventManagerImpl::EventManagerImpl()
{}

frts::EventManagerImpl::~EventManagerImpl()
{}

void frts::EventManagerImpl::checkRequiredData(SharedManagerPtr)
{}

bool frts::EventManagerImpl::createData(SharedManagerPtr)
{
    return false;
}

std::string frts::EventManagerImpl::getName() const
{
    return EventIds::eventManager();
}

std::vector<std::string> frts::EventManagerImpl::getSupportedConfig()
{
    return {};
}

std::string frts::EventManagerImpl::getTypeName() const
{
    return getName();
}

int frts::EventManagerImpl::getTypeVersion() const
{
    return getVersion();
}

int frts::EventManagerImpl::getVersion() const
{
    return 1;
}

bool frts::EventManagerImpl::init(SharedManagerPtr shared)
{
    // TODO Implement frts::EventManagerImpl::init().

    isInit = true;
    return false;
}

bool frts::EventManagerImpl::isInitialized() const
{
    return isInit;
}

bool frts::EventManagerImpl::isPreInitialized() const
{
    return isPreInit;
}

void frts::EventManagerImpl::parseConfig(const std::string&, ConfigNodePtr, SharedManagerPtr)
{}

bool frts::EventManagerImpl::preInit(SharedManagerPtr)
{
    isPreInit = true;
    return false;
}

void frts::EventManagerImpl::validateData(SharedManagerPtr)
{}

void frts::EventManagerImpl::validateModules(SharedManagerPtr)
{}
