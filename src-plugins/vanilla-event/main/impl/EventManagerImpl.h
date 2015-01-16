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

        bool init(const SharedManagerPtr& shared) override;

        EventPtr makeEvent(const IdPtr& type, const SharedManagerPtr& shared) override;
        EventValuePtr makeEventValue(const IdPtr& type, const SharedManagerPtr& shared) override;
        void raise(const EventPtr& event, const SharedManagerPtr& shared) override;
        void registerEventValueBuilder(const IdPtr& type, const EventValueBuilderPtr& builder) override;
        void subscribe(const EventObserverPtr& observer, const IdPtr& type) override;
        void unsubscribe(const EventObserverPtr& observer) override;
        void unsubscribe(const EventObserverPtr& observer, const IdPtr& type) override;

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
