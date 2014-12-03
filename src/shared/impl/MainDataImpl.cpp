#include "MainDataImpl.h"

#include <shared/MainIds.h>


frts::MainDataImpl::MainDataImpl(const std::string& pluginPath)
    : pluginPath{pluginPath}
{
}

std::string frts::MainDataImpl::getName() const
{
    return MainIds::MainData();
}

std::string frts::MainDataImpl::getPluginPath() const
{
    return pluginPath;
}

std::string frts::MainDataImpl::getTypeName() const
{
    return getName();
}

int frts::MainDataImpl::getTypeVersion() const
{
    return 1;
}

int frts::MainDataImpl::getVersion() const
{
    return 1;
}
