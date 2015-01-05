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
     * @brief The action manager handles the currently running user action and allows to stop it.
     */
    class ActionManager : public Tickable
    {
    public:
        virtual ~ActionManager() {}

        /**
         * @brief Set a new action as the currently running. This will stop/cancel the previously.
         * @param action The action.
         * @param shared The shared manager.
         */
        virtual void newAction(ActionPtr action, SharedManagerPtr shared) = 0;

        /**
         * @brief Stop/Cancel the currently running action.
         * @param shared The shared manager.
         */
        virtual void stopAction(SharedManagerPtr shared) = 0;
    };
}

#endif // FRTS_ACTIONMANAGER

