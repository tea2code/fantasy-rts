#ifndef FRTS_EVENTOBSERVER
#define FRTS_EVENTOBSERVER

#include "Event.h"

#include <memory>


namespace frts
{
    class EventObserver;

    /**
     * @brief Pointer to EventObserver.
     */
    using EventObserverPtr = std::shared_ptr<EventObserver>;

    /**
     * @brief An event observer can register to the event manager and receive
     *        events.
     */
    class EventObserver
    {
    public:
        virtual ~EventObserver() {}

        /**
         * @brief Notify the observer regarding a new event.
         * @param event The event.
         * @param shared The shared manager.
         */
        virtual void notify(const EventPtr& event, const SharedManagerPtr& shared) = 0;
    };
}

#endif // FRTS_EVENTOBSERVER

