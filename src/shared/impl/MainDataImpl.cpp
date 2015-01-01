#include "MainDataImpl.h"

#include <shared/MainIds.h>


frts::MainDataImpl::MainDataImpl(const std::string& pluginPath, Frame::time deltaTime)
    : deltaTime{deltaTime}, pluginPath{pluginPath}
{
}

frts::Frame::time frts::MainDataImpl::getDeltaTime() const
{
    return deltaTime;
}

std::string frts::MainDataImpl::getName() const
{
    return MainIds::mainData();
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
    return getVersion();
}

int frts::MainDataImpl::getVersion() const
{
    return 2;
}
