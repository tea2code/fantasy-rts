#ifndef FRTS_EVENTMANAGER
#define FRTS_EVENTMANAGER

#include "Event.h"
#include "EventObserver.h"
#include "EventValue.h"
#include "EventValueBuilder.h"
#include <frts/shared>
#include <frts/module>

#include <memory>


namespace frts
{
    class EventManager;

    /**
     * @brief Pointer to EventManager.
     */
    using EventManagerPtr = std::shared_ptr<EventManager>;

    /**
     * @brief Interface for event manager. Allows to register and make event types and
     *        subscribe for different event types which then can be send.
     */
    class EventManager : public Utility
    {
    public:
        virtual ~EventManager() {}

        /**
         * @brief Create a new event.
         * @param type The event type.
         * @param shared The shared manager.
         * @return The event.
         */
        virtual EventPtr makeEvent(IdPtr type, SharedManagerPtr shared) = 0;

        /**
         * @brief Create a new event value.
         * @param type The event value type.
         * @param shared The shared manager.
         * @return The event value.
         */
        virtual EventValuePtr makeEventValue(IdPtr type, SharedManagerPtr shared) = 0;

        /**
         * @brief Raise a new event. Every event observer which has registered to this event
         *        type will be notified.
         * @param event The event.
         */
        virtual void raise(EventPtr event) = 0;

        /**
         * @brief Register an event value builder.
         * @param type The event value type for which this builder is registered.
         * @param builder The event value builder.
         */
        virtual void registerEventValueBuilder(IdPtr type, EventValueBuilderPtr builder) = 0;

        /**
         * @brief Subscribe to given event type.
         * @param observer The event observer.
         * @param type The event type.
         */
        virtual void subscribe(EventObserverPtr observer, IdPtr type) = 0;

        /**
         * @brief Unsubcribe from all events.
         * @param observer The observer.
         */
        virtual void unsubscribe(EventObserverPtr observer) = 0;

        /**
         * @brief Unsubcribe from given event type.
         * @param observer The observer.
         * @param type The type.
         */
        virtual void unsubscribe(EventObserverPtr observer, IdPtr type) = 0;
    };

    /**
     * @brief Helper function to create a new event value.
     * @param eventManager The event manager.
     * @param type The event value type.
     * @param shared The shared manager.
     * @return The event value.
     */
    template<class EventValue>
    std::shared_ptr<EventValue> makeEventValue(EventManagerPtr eventManager, const std::string& type, SharedManagerPtr shared)
    {
        auto typeId = shared->makeId(type);
        return std::static_pointer_cast<EventValue>(eventManager->makeEventValue(typeId, shared));
    }
}

#endif // FRTS_EVENTMANAGER

