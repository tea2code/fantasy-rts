#ifndef FRTS_EVENTVALUE
#define FRTS_EVENTVALUE

#include <frts/shared>

#include <memory>


namespace frts
{
    class EventValue;

    /**
     * @brief Pointer to EventValue.
     */
    using EventValuePtr = std::shared_ptr<EventValue>;

    /**
     * @brief An event value stores data associated with an event.
     */
    class EventValue
    {
    public:
        virtual ~EventValue() {}

        /**
         * @brief Get the event value type.
         * @return The event value type.
         */
        virtual IdPtr getType() const = 0;
    };
}

#endif // FRTS_EVENTVALUE

