#ifndef FRTS_ACTIONHANDLER_H
#define FRTS_ACTIONHANDLER_H

#include "Action.h"

#include <frts/module>

#include <memory>


namespace frts
{
    class ActionHandler;

    /**
     * @brief Pointer to ActionHandler.
     */
    using ActionHandlerPtr = std::shared_ptr<ActionHandler>;

    /**
     * @brief The action handlers handles the currently running user action and allows to stop it.
     */
    class ActionHandler : public Tickable
    {
    public:
        ActionHandler();
        ~ActionHandler();

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/ActionHandler";
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

        void newAction(ActionPtr action, SharedManagerPtr shared);
        bool stopAction(SharedManagerPtr shared);

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
     * @brief Create a new action handler.
     * @return The action handler.
     */
    inline ActionHandlerPtr makeActionHandler()
    {
        return std::make_shared<ActionHandler>();
    }
}

#endif // FRTS_ACTIONHANDLER_H
