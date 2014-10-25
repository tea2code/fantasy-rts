#include "MainDataImpl.h"


frts::MainDataImpl::MainDataImpl(const std::string& pluginPath)
    : pluginPath{pluginPath}
{
}

std::string frts::MainDataImpl::getName() const
{
    return "frts::MainData";
}

std::string frts::MainDataImpl::getPluginPath() const
{
    return pluginPath;
}
