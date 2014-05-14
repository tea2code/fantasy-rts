#include "SharedManagerImpl.h"

#include <shared/DataValue.h>
#include "IdImpl.h"

#include <boost/format.hpp>

#include <memory>


const std::string frts::SharedManagerImpl::logModule = "SharedManager";

frts::SharedManagerImpl::SharedManagerImpl(LogPtr log)
    : log{log}, quitApplication{false}
{
    if (log == nullptr)
    {
        throw std::invalid_argument("Log must not be null.");
    }
}

frts::SharedManagerImpl::~SharedManagerImpl()
{
}

frts::DataValuePtr frts::SharedManagerImpl::getDataValue(IdPtr id) const
{
    auto it = dataValues.find(id);
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
    auto it = utilityModules.find(id);
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
    if (frame == nullptr)
    {
        throw std::invalid_argument("Frame must not be null.");
    }

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
    if (utility == nullptr)
    {
        throw std::invalid_argument("Utility must not be null.");
    }

    utilityModules[id] = utility;
}

void frts::SharedManagerImpl::setDataValue(IdPtr id, DataValuePtr value)
{
    if (value == nullptr)
    {
        throw std::invalid_argument("Data value must not be null.");
    }

    dataValues[id] = value;
}

frts::TickableItr frts::SharedManagerImpl::updateModulesBegin() const
{
    return updateModules.begin();
}

frts::TickableItr frts::SharedManagerImpl::updateModulesEnd() const
{
    return updateModules.end();
}
