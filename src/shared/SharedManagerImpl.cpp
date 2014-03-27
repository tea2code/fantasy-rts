#include "SharedManagerImpl.h"


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
    throw 42;
}

const frts::FramePtr frts::SharedManagerImpl::getFrame() const
{
    throw 42;
}

frts::LogPtr frts::SharedManagerImpl::getLog() const
{
    throw 42;
}

frts::UtilityPtr frts::SharedManagerImpl::getUtility(IdPtr id) const
{
    throw 42;
}

frts::IdPtr frts::SharedManagerImpl::makeId(const std::string& str) const
{
    throw 42;
}

frts::TickableItr frts::SharedManagerImpl::renderModulesBegin() const
{
    throw 42;
}

frts::TickableItr frts::SharedManagerImpl::renderModulesEnd() const
{
    throw 42;
}

void frts::SharedManagerImpl::setFrame(FramePtr frame)
{
    this->frame = frame;
}

void frts::SharedManagerImpl::setUtility(IdPtr id, UtilityPtr utility)
{
    throw 42;
}

void frts::SharedManagerImpl::setValue(IdPtr id, DataValuePtr value)
{
    throw 42;
}

frts::TickableItr frts::SharedManagerImpl::updateModulesBegin() const
{
    throw 42;
}

frts::TickableItr frts::SharedManagerImpl::updateModulesEnd() const
{
    throw 42;
}
