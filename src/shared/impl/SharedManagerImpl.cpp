#include "SharedManagerImpl.h"

#include <shared/DataValue.h>
#include "IdImpl.h"

#include <boost/format.hpp>

#include <memory>


frts::SharedManagerImpl::SharedManagerImpl(const LogPtr& log)
    : log{log}, quitApplication{false}
{
}

frts::SharedManagerImpl::~SharedManagerImpl()
{
}

frts::DataValuePtr frts::SharedManagerImpl::getDataValue(const IdPtr& id) const
{
    assert(id != nullptr);

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

std::vector<frts::DataValuePtr> frts::SharedManagerImpl::getDataValues() const
{
    std::vector<frts::DataValuePtr> result;
    for(auto it : dataValues)
    {
        result.push_back(it.second);
    }
    return result;
}

const frts::FramePtr frts::SharedManagerImpl::getFrame() const
{
    return frame;
}

frts::LogPtr frts::SharedManagerImpl::getLog() const
{
    return log;
}

frts::UtilityPtr frts::SharedManagerImpl::getUtility(const IdPtr& id) const
{
    assert(id != nullptr);

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

frts::IdNotFoundError frts::SharedManagerImpl::makeIdNotFoundError(const IdPtr& id) const
{
    assert(id != nullptr);

    auto msg = boost::format(R"(SharedManager: Id "%1%" could not be found.)") % id->toString();
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

void frts::SharedManagerImpl::setFrame(const FramePtr& frame)
{
    if (frame == nullptr)
    {
        throw std::invalid_argument("SharedManager: Frame must not be null.");
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

void frts::SharedManagerImpl::setUtility(const IdPtr& id, const UtilityPtr& utility)
{
    assert(id != nullptr);
    assert(utility != nullptr);

    utilityModules[id] = utility;
}

void frts::SharedManagerImpl::setDataValue(const IdPtr& id, const DataValuePtr& value)
{
    assert(id != nullptr);
    assert(value != nullptr);

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
