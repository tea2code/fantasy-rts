#ifndef FRTS_ACTIONMANAGERIMPL_H
#define FRTS_ACTIONMANAGERIMPL_H

#include <main/ActionHandler.h>
#include <main/ActionManager.h>


namespace frts
{
    class ActionManagerImpl : public ActionManager
    {
    public:
        /**
         * @param actionHandler The action handler.
         */
        ActionManagerImpl(ActionHandlerPtr actionHandler);

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/ActionManager";
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

        void newAction(ActionPtr action, SharedManagerPtr shared) override;
        bool stopAction(SharedManagerPtr shared) override;

    private:
        bool isInit = false;
        bool isPreInit = false;

        ActionHandlerPtr actionHandler;
    };

    /**
     * @brief Create a new action manager.
     * @param actionHandler The action handler.
     * @return The action manager.
     */
    inline ActionManagerPtr makeActionManager(ActionHandlerPtr actionHandler)
    {
        return std::make_shared<ActionManagerImpl>(actionHandler);
    }
}

#endif // FRTS_ACTIONMANAGERIMPL_H
