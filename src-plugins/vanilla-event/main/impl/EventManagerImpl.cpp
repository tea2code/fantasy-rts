#include "EventManagerImpl.h"

#include "StringEventValueBuilder.h"
#include "IntegerEventValueBuilder.h"
#include "FloatEventValueBuilder.h"
#include "BooleanEventValueBuilder.h"
#include "IdEventValueBuilder.h"
#include <main/EventError.h>
#include <main/EventIds.h>

#include <utility>


frts::EventManagerImpl::EventManagerImpl()
{}

frts::EventManagerImpl::~EventManagerImpl()
{}

void frts::EventManagerImpl::checkRequiredData(SharedManagerPtr)
{}

bool frts::EventManagerImpl::createData(SharedManagerPtr)
{
    return false;
}

std::string frts::EventManagerImpl::getName() const
{
    return EventIds::eventManager();
}

std::vector<std::string> frts::EventManagerImpl::getSupportedConfig()
{
    return {};
}

std::string frts::EventManagerImpl::getTypeName() const
{
    return getName();
}

int frts::EventManagerImpl::getTypeVersion() const
{
    return getVersion();
}

int frts::EventManagerImpl::getVersion() const
{
    return 1;
}

bool frts::EventManagerImpl::init(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    // Event values:
    // String.
    auto eventValueType = shared->makeId(EventIds::stringEventValue());
    registerEventValueBuilder(eventValueType, makeStringEventValueBuilder(eventValueType));

    // Integer.
    eventValueType = shared->makeId(EventIds::integerEventValue());
    registerEventValueBuilder(eventValueType, makeIntegerEventValueBuilder(eventValueType));

    // Float.
    eventValueType = shared->makeId(EventIds::floatEventValue());
    registerEventValueBuilder(eventValueType, makeFloatEventValueBuilder(eventValueType));

    // Boolean.
    eventValueType = shared->makeId(EventIds::booleanEventValue());
    registerEventValueBuilder(eventValueType, makeBooleanEventValueBuilder(eventValueType));

    // Id.
    eventValueType = shared->makeId(EventIds::idEventValue());
    registerEventValueBuilder(eventValueType, makeIdEventValueBuilder(eventValueType));

    isInit = true;
    return false;
}

bool frts::EventManagerImpl::isInitialized() const
{
    return isInit;
}

bool frts::EventManagerImpl::isPreInitialized() const
{
    return isPreInit;
}

frts::EventValuePtr frts::EventManagerImpl::makeEventValue(IdPtr type, SharedManagerPtr shared)
{
    assert(type != nullptr);
    assert(shared != nullptr);

    auto it = eventValueBuilders.find(type);
    if(it != eventValueBuilders.end())
    {
        return it->second->build(shared);
    }
    else
    {
        auto msg = boost::format(R"(%2%: No event value builder is registered for ID "%1%".)") % type->toString() % getName();
        throw UnknownEventValueBuilderError(msg.str());
    }
}

void frts::EventManagerImpl::parseConfig(const std::string&, ConfigNodePtr, SharedManagerPtr)
{}

bool frts::EventManagerImpl::preInit(SharedManagerPtr)
{
    isPreInit = true;
    return false;
}

void frts::EventManagerImpl::registerEventValueBuilder(IdPtr type, EventValueBuilderPtr builder)
{
    assert(type != nullptr);
    assert(builder != nullptr);

    eventValueBuilders.insert(std::make_pair(type, builder));
}

void frts::EventManagerImpl::validateData(SharedManagerPtr)
{}

void frts::EventManagerImpl::validateModules(SharedManagerPtr)
{}
