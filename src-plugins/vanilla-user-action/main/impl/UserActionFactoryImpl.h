#ifndef FRTS_USERACTIONFACTORYIMPL_H
#define FRTS_USERACTIONFACTORYIMPL_H

#include <main/UserActionFactory.h>
#include <frts/BaseUtility.h>

#include <stdexcept>
#include <unordered_map>


namespace frts
{
    /**
     * @brief Thrown if an unknown user action is configured.
     */
    class UnknownUserActionError : public std::runtime_error
    {
    public:
        explicit UnknownUserActionError(const std::string& msg) : std::runtime_error(msg) {}
    };

    /**
     * @brief This factory will register all commands, actions and jobs of this plugin.
     */
    class UserActionFactoryImpl : public BaseUtility<UserActionFactory>
    {
    public:
        UserActionFactoryImpl();
        ~UserActionFactoryImpl();

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

        void createDrops(const EntityPtr& entity, const PointPtr& pos, const SharedManagerPtr& shared) override;
        void confirmJobsValidOrStop(const PointPtr& pos, const SharedManagerPtr& shared) override;
        bool findPathToJob(const EntityPtr& entity, const PointPtr& jobPos, bool toNeighbor,
                           const SharedManagerPtr& shared) override;
        MoveEntityResult moveEntity(const EntityPtr& entity, const SharedManagerPtr& shared) override;

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
        return std::make_shared<UserActionFactoryImpl>();
    }
}

#endif // FRTS_USERACTIONFACTORYIMPL_H
