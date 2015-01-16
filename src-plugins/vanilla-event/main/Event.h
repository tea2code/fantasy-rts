#ifndef FRTS_EVENT
#define FRTS_EVENT

#include "EventValue.h"
#include <frts/shared>

#include <memory>


namespace frts
{
    class Event;

    /**
     * @brief Pointer to Event.
     */
    using EventPtr = std::shared_ptr<Event>;

    /**
     * @brief Event container consisting of the event type and
     *        multiple event values.
     */
    class Event
    {
    public:
        virtual ~Event() {}

        /**
         * @brief Get the event type.
         * @return The event type.
         */
        virtual IdPtr getType() const = 0;

        /**
         * @brief Get an event value.
         * @throws EventValueNotFoundError if value for this id is not found.
         * @param valueId The value id.
         * @return The value.
         */
        virtual EventValuePtr getValue(const IdPtr& valueId) const = 0;

        /**
         * @brief Check if a value with given id exists.
         * @param valueId The value id.
         * @return True if the value exists else false.
         */
        virtual bool hasValue(const IdPtr& valueId) const = 0;

        /**
         * @brief Set the value.
         * @param valueId The value id.
         * @param value The value.
         */
        virtual void setValue(const IdPtr& valueId, const EventValuePtr& value) = 0;
    };

    /**
     * @brief Get an event value. You should check hasValue() before to prevent an exception.
     * @throws EventValueNotFoundError if value for this id is not found.
     * @param event The event.
     * @param valueId The value id.
     * @return The event value.
     */
    template<class EventValue>
    std::shared_ptr<EventValue> getEventValue(EventPtr event, IdPtr valueId)
    {
        return std::static_pointer_cast<EventValue>(event->getValue(valueId));
    }
}

#endif // FRTS_EVENT

