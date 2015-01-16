#ifndef FRTS_ACTIONMANAGER
#define FRTS_ACTIONMANAGER

#include "Action.h"

#include <frts/module>
#include <frts/shared>

#include <memory>


namespace frts
{
    class ActionManager;

    /**
     * @brief Pointer to ActionManager.
     */
    using ActionManagerPtr = std::shared_ptr<ActionManager>;

    /**
     * @brief The action manager forwards commands to the action handler.
     */
    class ActionManager : public Utility
    {
    public:
        virtual ~ActionManager() {}

        /**
         * @brief Set a new action as the currently running. This will stop/cancel the previously.
         * @param action The action.
         * @param shared The shared manager.
         */
        virtual void newAction(const ActionPtr& action, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Stop/Cancel the currently running action.
         * @param shared The shared manager.
         * @return True if there was an action to stop else false.
         */
        virtual bool stopAction(const SharedManagerPtr& shared) = 0;
    };
}

#endif // FRTS_ACTIONMANAGER

