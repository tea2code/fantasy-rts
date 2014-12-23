#ifndef FRTS_EVENTMANAGER
#define FRTS_EVENTMANAGER

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


    };
}

#endif // FRTS_EVENTMANAGER

