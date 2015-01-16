#include "MainDataImpl.h"

#include <shared/MainIds.h>


frts::MainDataImpl::MainDataImpl(const std::string& pluginPath, Frame::time deltaTime)
    : BaseDataValue(MainIds::mainData(), 2, MainIds::mainData(), 2),
      deltaTime{deltaTime}, pluginPath{pluginPath}
{
}

frts::Frame::time frts::MainDataImpl::getDeltaTime() const
{
    return deltaTime;
}

std::string frts::MainDataImpl::getPluginPath() const
{
    return pluginPath;
}
