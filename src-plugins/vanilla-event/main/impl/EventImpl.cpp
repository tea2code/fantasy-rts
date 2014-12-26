#include "EventImpl.h"

#include <main/EventError.h>

#include <boost/format.hpp>

#include <utility>


frts::EventImpl::EventImpl(IdPtr type)
    : type{type}
{

}

frts::IdPtr frts::EventImpl::getType() const
{
    return type;
}

frts::EventValuePtr frts::EventImpl::getValue(IdPtr valueId) const
{
    assert(valueId != nullptr);

    auto it = eventValues.find(valueId);
    if (it != eventValues.end())
    {
        return it->second;
    }
    else
    {
        auto msg = boost::format(R"(Event "%1%": No event value found for id "%2%".)")
                % type->toString() % valueId->toString();
        throw EventValueNotFoundError(msg.str());
    }
}

bool frts::EventImpl::hasValue(IdPtr valueId) const
{
    assert(valueId != nullptr);

    return eventValues.find(valueId) != eventValues.end();
}

void frts::EventImpl::setValue(IdPtr valueId, EventValuePtr value)
{
    assert(valueId != nullptr);
    assert(value != nullptr);

    eventValues.insert(std::make_pair(valueId, value));
}
