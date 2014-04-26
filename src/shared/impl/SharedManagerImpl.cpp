#include "SharedManagerImpl.h"

#include <shared/DataValue.h>
#include "IdImpl.h"

#include <boost/format.hpp>

#include <memory>


const std::string frts::SharedManagerImpl::logModule = "SharedManager";

frts::SharedManagerImpl::SharedManagerImpl(LogPtr log)
    : log{log}, quitApplication{false}
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

const frts::FramePtr frts::SharedManagerImpl::getFrame() const
{
    return frame;
}

frts::LogPtr frts::SharedManagerImpl::getLog() const
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

bool frts::SharedManagerImpl::isQuitApplication() const
{
    return quitApplication;
}

frts::IdPtr frts::SharedManagerImpl::makeId(const std::string& str) const
{
    return frts::makeId(str);
}

frts::IdNotFoundError frts::SharedManagerImpl::makeIdNotFoundError(IdPtr id) const
{
    auto msg = boost::format(R"(Id "%1%" could not be found.)") % id->toString();
    return IdNotFoundError(msg.str());
}

frts::TickableItr frts::SharedManagerImpl::renderModulesBegin() const
{
    return renderModules.begin();
}

frts::TickableItr frts::SharedManagerImpl::renderModulesEnd() const
{
    return renderModules.end();
}

void frts::SharedManagerImpl::setFrame(FramePtr frame)
{
    this->frame = frame;
}

void frts::SharedManagerImpl::setRenderModules(const std::vector<frts::TickablePtr>& modules)
{
    renderModules = modules;
}

void frts::SharedManagerImpl::setQuitApplication(bool quit)
{
    quitApplication = quit;
}

void frts::SharedManagerImpl::setUpdateModules(const std::vector<frts::TickablePtr>& modules)
{
    updateModules = modules;
}

void frts::SharedManagerImpl::setUtility(IdPtr id, UtilityPtr utility)
{
    utilityModules[id->toString()] = utility;
}

void frts::SharedManagerImpl::setDataValue(IdPtr id, DataValuePtr value)
{
    dataValues[id->toString()] = value;
}

frts::TickableItr frts::SharedManagerImpl::updateModulesBegin() const
{
    return updateModules.begin();
}

frts::TickableItr frts::SharedManagerImpl::updateModulesEnd() const
{
    return updateModules.end();
}
