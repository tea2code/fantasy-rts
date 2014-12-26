#ifndef FRTS_EVENTMANAGERIMPL_H
#define FRTS_EVENTMANAGERIMPL_H

#include <main/EventManager.h>

#include <unordered_map>


namespace frts
{
    class EventManagerImpl : public EventManager
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

        void checkRequiredData(SharedManagerPtr shared) override;
        bool createData(SharedManagerPtr shared) override;
        std::string getName() const override;
        std::vector<std::string> getSupportedConfig() override;
        std::string getTypeName() const override;
        int getTypeVersion() const override;
        int getVersion() const override;
        bool init(SharedManagerPtr shared) override;
        bool isInitialized() const override;
        bool isPreInitialized() const override;
        void parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared) override;
        bool preInit(SharedManagerPtr shared) override;
        void validateData(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

        EventPtr makeEvent(IdPtr type, SharedManagerPtr shared) override;
        EventValuePtr makeEventValue(IdPtr type, SharedManagerPtr shared) override;
        void registerEventValueBuilder(IdPtr type, EventValueBuilderPtr builder) override;

    private:
        using EventValueBuilderMap = std::unordered_map<IdPtr, EventValueBuilderPtr, IdHash, IdEqual>;

    private:
        EventValueBuilderMap eventValueBuilders;

        bool isInit = false;
        bool isPreInit = false;
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
