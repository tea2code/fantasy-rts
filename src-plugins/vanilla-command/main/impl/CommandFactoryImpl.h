#ifndef FRTS_COMMANDFACTORYIMPL_H
#define FRTS_COMMANDFACTORYIMPL_H

#include <main/CommandFactory.h>
#include <frts/BaseUtility.h>

#include <list>
#include <memory>
#include <unordered_map>


namespace frts
{
    class CommandFactoryImpl : public BaseUtility<CommandFactory>
    {
    public:
        CommandFactoryImpl();

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/CommandFactory";
        }

        void addToUndo(const CommandPtr& command, const SharedManagerPtr& shared) override;
        void checkRequiredData(const SharedManagerPtr& shared) override;
        bool createData(const SharedManagerPtr& shared) override;
        std::vector<std::string> getSupportedConfig() override;
        bool init(const SharedManagerPtr& shared) override;
        CommandPtr makeCommand(const IdPtr& builderId, const SharedManagerPtr& shared) override;
        void parseConfig(const std::string& key, const ConfigNodePtr& node, const SharedManagerPtr& shared) override;
        void registerCommandBuilder(const IdPtr& builderId, const CommandBuilderPtr& builder) override;
        void undoLastCommand(const SharedManagerPtr& shared) override;

    private:
        using CommandBuilderMap = std::unordered_map<IdPtr, CommandBuilderPtr>;

    private:
        CommandBuilderMap commandBuilders;
        std::list<CommandPtr> undoQueue;
    };

    /**
     * @brief Create new command factory.
     * @return The command factory.
     */
    inline CommandFactoryPtr makeCommandFactory()
    {
        return std::make_shared<CommandFactoryImpl>();
    }
}

#endif // FRTS_COMMANDFACTORYIMPL_H
