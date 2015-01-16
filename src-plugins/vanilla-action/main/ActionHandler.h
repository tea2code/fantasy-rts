#ifndef FRTS_ACTIONHANDLER_H
#define FRTS_ACTIONHANDLER_H

#include "Action.h"

#include <frts/BaseTickable.h>

#include <memory>


namespace frts
{
    class ActionHandler;

    /**
     * @brief Pointer to ActionHandler.
     */
    using ActionHandlerPtr = std::shared_ptr<ActionHandler>;

    /**
     * @brief The action handlers runs the current user action and allows to stop it.
     */
    class ActionHandler : public BaseTickable<Tickable>
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

        void tick(const SharedManagerPtr& shared) override;

        /**
         * @brief Set a new action as the currently running. This will stop/cancel the previously.
         * @param action The action.
         * @param shared The shared manager.
         */
        void newAction(const ActionPtr& action, const SharedManagerPtr& shared);

        /**
         * @brief Stop/Cancel the currently running action.
         * @param shared The shared manager.
         * @return True if there was an action to stop else false.
         */
        bool stopAction(const SharedManagerPtr& shared);

    private:
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
