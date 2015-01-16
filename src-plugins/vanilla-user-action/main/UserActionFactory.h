#ifndef FRTS_USERACTIONFACTORY_H
#define FRTS_USERACTIONFACTORY_H

#include <frts/BaseUtility.h>

#include <unordered_map>


namespace frts
{
    /**
     * @brief This factory will register all commands, actions and jobs of this plugin.
     */
    class UserActionFactory : public BaseUtility<Utility>
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

        std::vector<std::string> getSupportedConfig() override;
        bool init(const SharedManagerPtr& shared) override;
        void parseConfig(const std::string& key, const ConfigNodePtr& node, const SharedManagerPtr& shared) override;
        void validateModules(const SharedManagerPtr& shared) override;

    private:
        /**
         * @brief Simple struct to store configuration of an command.
         */
        struct CommandConfig
        {
            IdPtr type;
            ConfigNodePtr settings;
        };

        /**
         * @brief Command config map.
         */
        using CommandConfigMap = std::unordered_map<IdPtr, CommandConfig>;

    private:
        CommandConfigMap commandConfigs;
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
