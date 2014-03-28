#include "SharedManagerImpl.h"

#include "IdImpl.h"

#include <boost/format.hpp>


frts::SharedManagerImpl::SharedManagerImpl(LogPtr log,
                                           std::vector<frts::TickablePtr> renderModules,
                                           std::vector<frts::TickablePtr> updateModules)
    : log{log},
      renderModules{renderModules},
      updateModules{updateModules}
{
}

frts::SharedManagerImpl::~SharedManagerImpl()
{
}

frts::DataValuePtr frts::SharedManagerImpl::getDataValue(IdPtr id) const
{
    std::map<IdPtr, DataValuePtr>::const_iterator it = dataValues.find(id);
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
    std::map<IdPtr, UtilityPtr>::const_iterator it = utilityModules.find(id);
    if(it != utilityModules.end())
    {
        return it->second;
    }
    else
    {
        throw makeIdNotFoundError(id);
    }
}

frts::IdPtr frts::SharedManagerImpl::makeId(const std::string& str) const
{
    return IdPtr(new IdImpl(str));
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

void frts::SharedManagerImpl::setUtility(IdPtr id, UtilityPtr utility)
{
    utilityModules[id] = utility;
}

void frts::SharedManagerImpl::setValue(IdPtr id, DataValuePtr value)
{
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
