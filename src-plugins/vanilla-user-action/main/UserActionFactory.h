#ifndef FRTS_USERACTIONFACTORY_H
#define FRTS_USERACTIONFACTORY_H

#include <frts/BaseUtility.h>


namespace frts
{
    /**
     * @brief This factory will register all commands, actions and jobs of this plugin.
     */
    class UserActionFactory : public BaseUtility
    {
    public:
        UserActionFactory();
        ~UserActionFactory();

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/UserActionFactory";
        }

        bool init(SharedManagerPtr shared) override;
    };

    /**
     * @brief Create a new user action factory.
     * @return The module.
     */
    inline UtilityPtr makeUserActionFactory()
    {
        return std::make_shared<UserActionFactory>();
    }
}

#endif // FRTS_USERACTIONFACTORY_H
