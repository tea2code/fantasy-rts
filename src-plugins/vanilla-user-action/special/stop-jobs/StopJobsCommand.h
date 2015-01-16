#ifndef FRTS_STOPJOBSCOMMAND_H
#define FRTS_STOPJOBSCOMMAND_H

#include <frts/vanillaaction>
#include <frts/vanillacommand>


namespace frts
{
    class StopJobsCommand : public Command
    {
    public:
        /**
         * @param commandType The command type.
         * @param settings The settings node.
         */
        StopJobsCommand(const IdPtr& commandType, const ConfigNodePtr& settings);
        ~StopJobsCommand();

        void execute(const SharedManagerPtr& shared) override;
        IdPtr getCommandType() const override;
        void undo(const SharedManagerPtr& shared) override;

    private:
        const std::string name = "frts::StopJobsCommand";

        IdPtr commandType;
        ConfigNodePtr settings;

        ActionPtr action;
    };

    /**
     * @brief Create new stop jobs command.
     * @param commandType The command type.
     * @param settings The settings node.
     * @return The command.
     */
    inline CommandPtr makeStopJobsCommand(const IdPtr& commandType, const ConfigNodePtr& settings)
    {
        assert(commandType != nullptr);
        assert(settings != nullptr);

        return std::make_shared<StopJobsCommand>(commandType, settings);
    }
}

#endif // FRTS_STOPJOBSCOMMAND_H
