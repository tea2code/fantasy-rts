#ifndef FRTS_ACTIONMANAGERIMPL_H
#define FRTS_ACTIONMANAGERIMPL_H

#include <main/ActionHandler.h>
#include <main/ActionManager.h>
#include <frts/BaseUtility.h>


namespace frts
{
    class ActionManagerImpl : public BaseUtility<ActionManager>
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

        bool init(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

        void newAction(ActionPtr action, SharedManagerPtr shared) override;
        bool stopAction(SharedManagerPtr shared) override;

    private:
        ActionHandlerPtr actionHandler;
    };

    /**
     * @brief Create a new action manager.
     * @param actionHandler The action handler.
     * @return The action manager.
     */
    inline ActionManagerPtr makeActionManager(ActionHandlerPtr actionHandler)
    {
        assert(actionHandler != nullptr);

        return std::make_shared<ActionManagerImpl>(actionHandler);
    }
}

#endif // FRTS_ACTIONMANAGERIMPL_H
