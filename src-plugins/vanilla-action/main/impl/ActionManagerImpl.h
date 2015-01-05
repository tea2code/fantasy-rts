#ifndef FRTS_ACTIONMANAGERIMPL_H
#define FRTS_ACTIONMANAGERIMPL_H

#include <main/ActionManager.h>


namespace frts
{
    class ActionManagerImpl : public ActionManager
    {
    public:
        ActionManagerImpl();

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
        void tick(SharedManagerPtr shared) override;
        void validateData(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

        void newAction(ActionPtr action, SharedManagerPtr shared) override;
        void stopAction(SharedManagerPtr shared) override;

    private:
        bool isInit = false;
        bool isPreInit = false;

        /**
         * @brief The currently running action. Null if no action is set.
         */
        ActionPtr currentAction;

        /**
         * @brief Indicates if current action is executing or stopping.
         */
        bool isExecuting = true;

        /**
         * @brief The next action to execute. Null if no action is set.
         */
        ActionPtr nextAction;

    private:
        /**
         * @brief End the current action and start the next one if available.
         */
        void endAction();
    };

    /**
     * @brief Create a new action manager.
     * @return The action manager.
     */
    inline ActionManagerPtr makeActionManager()
    {
        return std::make_shared<ActionManagerImpl>();
    }
}

#endif // FRTS_ACTIONMANAGERIMPL_H
