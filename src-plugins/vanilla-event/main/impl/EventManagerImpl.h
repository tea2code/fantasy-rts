#ifndef FRTS_EVENTMANAGERIMPL_H
#define FRTS_EVENTMANAGERIMPL_H

#include <main/EventManager.h>
#include <frts/BaseUtility.h>

#include <unordered_map>


namespace frts
{
    class EventManagerImpl : public BaseUtility<EventManager>
    {
    public:
        EventManagerImpl();
        ~EventManagerImpl();

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/EventManager";
        }

        bool init(SharedManagerPtr shared) override;

        EventPtr makeEvent(IdPtr type, SharedManagerPtr shared) override;
        EventValuePtr makeEventValue(IdPtr type, SharedManagerPtr shared) override;
        void raise(EventPtr event, SharedManagerPtr shared) override;
        void registerEventValueBuilder(IdPtr type, EventValueBuilderPtr builder) override;
        void subscribe(EventObserverPtr observer, IdPtr type) override;
        void unsubscribe(EventObserverPtr observer) override;
        void unsubscribe(EventObserverPtr observer, IdPtr type) override;

    private:
        using EventValueBuilderMap = std::unordered_map<IdPtr, EventValueBuilderPtr>;
        using EventObserverMap = std::unordered_map<IdPtr, std::vector<EventObserverPtr>>;

    private:
        EventValueBuilderMap eventValueBuilders;
        EventObserverMap eventObservers;
    };

    /**
     * @brief Create new EventManager.
     * @return The event manager.
     */
    inline EventManagerPtr makeEventManager()
    {
        return std::make_shared<EventManagerImpl>();
    }
}

#endif // FRTS_EVENTMANAGERIMPL_H
