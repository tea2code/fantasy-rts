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
        ActionManagerImpl(const ActionHandlerPtr& actionHandler);

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/ActionManager";
        }

        bool init(const SharedManagerPtr& shared) override;
        void validateModules(const SharedManagerPtr& shared) override;

        void newAction(const ActionPtr& action, const SharedManagerPtr& shared) override;
        bool stopAction(const SharedManagerPtr& shared) override;

    private:
        ActionHandlerPtr actionHandler;
    };

    /**
     * @brief Create a new action manager.
     * @param actionHandler The action handler.
     * @return The action manager.
     */
    inline ActionManagerPtr makeActionManager(const ActionHandlerPtr& actionHandler)
    {
        assert(actionHandler != nullptr);

        return std::make_shared<ActionManagerImpl>(actionHandler);
    }
}

#endif // FRTS_ACTIONMANAGERIMPL_H
