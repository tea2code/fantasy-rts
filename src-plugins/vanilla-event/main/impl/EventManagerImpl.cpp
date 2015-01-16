#include "EventManagerImpl.h"

#include "EventImpl.h"
#include "StringEventValueBuilder.h"
#include "StringListEventValueBuilder.h"
#include "IntegerEventValueBuilder.h"
#include "IntegerListEventValueBuilder.h"
#include "FloatEventValueBuilder.h"
#include "FloatListEventValueBuilder.h"
#include "BooleanEventValueBuilder.h"
#include "BooleanListEventValueBuilder.h"
#include "IdEventValueBuilder.h"
#include "IdListEventValueBuilder.h"
#include <main/EventError.h>
#include <main/EventIds.h>

#include <algorithm>
#include <utility>


frts::EventManagerImpl::EventManagerImpl()
    : BaseUtility(EventIds::eventManager(), 1, EventIds::eventManager(), 1)
{}

frts::EventManagerImpl::~EventManagerImpl()
{}

bool frts::EventManagerImpl::init(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    // Event values:
    // String.
    auto eventValueType = shared->makeId(EventIds::stringEventValue());
    registerEventValueBuilder(eventValueType, makeStringEventValueBuilder(eventValueType));

    // String list.
    eventValueType = shared->makeId(EventIds::stringListEventValue());
    registerEventValueBuilder(eventValueType, makeStringListEventValueBuilder(eventValueType));

    // Integer.
    eventValueType = shared->makeId(EventIds::integerEventValue());
    registerEventValueBuilder(eventValueType, makeIntegerEventValueBuilder(eventValueType));

    // Integer list.
    eventValueType = shared->makeId(EventIds::integerListEventValue());
    registerEventValueBuilder(eventValueType, makeIntegerListEventValueBuilder(eventValueType));

    // Float.
    eventValueType = shared->makeId(EventIds::floatEventValue());
    registerEventValueBuilder(eventValueType, makeFloatEventValueBuilder(eventValueType));

    // Float list.
    eventValueType = shared->makeId(EventIds::floatListEventValue());
    registerEventValueBuilder(eventValueType, makeFloatListEventValueBuilder(eventValueType));

    // Boolean.
    eventValueType = shared->makeId(EventIds::booleanEventValue());
    registerEventValueBuilder(eventValueType, makeBooleanEventValueBuilder(eventValueType));

    // Boolean list.
    eventValueType = shared->makeId(EventIds::booleanListEventValue());
    registerEventValueBuilder(eventValueType, makeBooleanListEventValueBuilder(eventValueType));

    // Id.
    eventValueType = shared->makeId(EventIds::idEventValue());
    registerEventValueBuilder(eventValueType, makeIdEventValueBuilder(eventValueType));

    // Id list.
    eventValueType = shared->makeId(EventIds::idListEventValue());
    registerEventValueBuilder(eventValueType, makeIdListEventValueBuilder(eventValueType));

    return BaseUtility::init(shared);
}

frts::EventPtr frts::EventManagerImpl::makeEvent(const IdPtr& type, const SharedManagerPtr&)
{
    assert(type != nullptr);

    return frts::makeEvent(type);
}

frts::EventValuePtr frts::EventManagerImpl::makeEventValue(const IdPtr& type, const SharedManagerPtr& shared)
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

void frts::EventManagerImpl::raise(const EventPtr& event, const SharedManagerPtr& shared)
{
    assert(event != nullptr);
    assert(shared != nullptr);

    auto it = eventObservers.find(event->getType());
    if (it != eventObservers.end())
    {
        auto& observers = it->second;
        std::for_each(observers.begin(), observers.end(), [&](auto& observer){ observer->notify(event, shared); });
    }
}

void frts::EventManagerImpl::registerEventValueBuilder(const IdPtr& type, const EventValueBuilderPtr& builder)
{
    assert(type != nullptr);
    assert(builder != nullptr);

    eventValueBuilders.insert(std::make_pair(type, builder));
}

void frts::EventManagerImpl::subscribe(const EventObserverPtr& observer, const IdPtr& type)
{
    eventObservers[type].push_back(observer);
}

void frts::EventManagerImpl::unsubscribe(const EventObserverPtr& observer)
{
    for (auto& eventObserver : eventObservers)
    {
        unsubscribe(observer, eventObserver.first);
    }
}

void frts::EventManagerImpl::unsubscribe(const EventObserverPtr& observer, const IdPtr& type)
{
    auto eoIt = eventObservers.find(type);
    if (eoIt != eventObservers.end())
    {
        auto& observers = eoIt->second;
        for (auto it = observers.begin(); it != observers.end();)
        {
            if(*it == observer)
            {
                it = observers.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}
