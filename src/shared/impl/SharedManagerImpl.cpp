#include "SharedManagerImpl.h"

#include <shared/DataValue.h>
#include "IdImpl.h"

#include <boost/format.hpp>

#include <memory>


const std::string frts::SharedManagerImpl::logModule = "SharedManager";

frts::SharedManagerImpl::SharedManagerImpl(LogPtr log)
    : log{log}
{
}

frts::SharedManagerImpl::~SharedManagerImpl()
{
}

frts::DataValuePtr frts::SharedManagerImpl::getDataValue(IdPtr id) const
{
    std::map<std::string, DataValuePtr>::const_iterator it = dataValues.find(id->toString());
    if(it != dataValues.end())
    {
        return it->second;
    }
    else
    {
        throw makeIdNotFoundError(id);
    }
}

const frts::FramePtr frts::SharedManagerImpl::getFrame() const noexcept
{
    return frame;
}

frts::LogPtr frts::SharedManagerImpl::getLog() const noexcept
{
    return log;
}

frts::UtilityPtr frts::SharedManagerImpl::getUtility(IdPtr id) const
{
    std::map<std::string, UtilityPtr>::const_iterator it = utilityModules.find(id->toString());
    if(it != utilityModules.end())
    {
        return it->second;
    }
    else
    {
        throw makeIdNotFoundError(id);
    }
}

frts::IdPtr frts::SharedManagerImpl::makeId(const std::string& str) const noexcept
{
    return frts::makeId(str);
}

frts::IdNotFoundError frts::SharedManagerImpl::makeIdNotFoundError(IdPtr id) const
{
    auto msg = boost::format(R"(Id "%1%" could not be found.)") % id->toString();
    return IdNotFoundError(msg.str());
}

frts::TickableItr frts::SharedManagerImpl::renderModulesBegin() const noexcept
{
    return renderModules.begin();
}

frts::TickableItr frts::SharedManagerImpl::renderModulesEnd() const noexcept
{
    return renderModules.end();
}

void frts::SharedManagerImpl::setFrame(FramePtr frame) noexcept
{
    this->frame = frame;
}

void frts::SharedManagerImpl::setRenderModules(const std::vector<frts::TickablePtr>& modules) noexcept
{
    renderModules = modules;
}

void frts::SharedManagerImpl::setUpdateModules(const std::vector<frts::TickablePtr>& modules) noexcept
{
    updateModules = modules;
}

void frts::SharedManagerImpl::setUtility(IdPtr id, UtilityPtr utility) noexcept
{
    utilityModules[id->toString()] = utility;
}

void frts::SharedManagerImpl::setDataValue(IdPtr id, DataValuePtr value) noexcept
{
    dataValues[id->toString()] = value;
}

frts::TickableItr frts::SharedManagerImpl::updateModulesBegin() const noexcept
{
    return updateModules.begin();
}

frts::TickableItr frts::SharedManagerImpl::updateModulesEnd() const noexcept
{
    return updateModules.end();
}
