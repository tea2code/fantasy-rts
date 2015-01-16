#ifndef FRTS_EVENTIMPL_H
#define FRTS_EVENTIMPL_H

#include <main/Event.h>

#include <unordered_map>


namespace frts
{
    class EventImpl : public Event
    {
    public:
        /**
         * @param type The event type.
         */
        EventImpl(const IdPtr& type);

        IdPtr getType() const override;
        EventValuePtr getValue(const IdPtr& valueId) const override;
        bool hasValue(const IdPtr& valueId) const override;
        void setValue(const IdPtr& valueId, const EventValuePtr& value) override;

    private:
        IdPtr type;
        std::unordered_map<IdPtr, EventValuePtr> eventValues;
    };

    /**
     * @brief Create a new Event.
     * @param type The event type.
     * @return The event.
     */
    inline EventPtr makeEvent(const IdPtr& type)
    {
        assert(type != nullptr);

        return std::make_shared<EventImpl>(type);
    }
}

#endif // FRTS_EVENTIMPL_H
