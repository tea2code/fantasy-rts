#ifndef FRTS_HARVESTCOMMAND_H
#define FRTS_HARVESTCOMMAND_H

#include <frts/vanillaaction>
#include <frts/vanillacommand>


namespace frts
{
    class HarvestCommand : public Command
    {
    public:
        /**
         * @param commandType The command type.
         * @param userActionType The user action type.
         * @param settings The settings node.
         */
        HarvestCommand(const IdPtr& commandType, const IdPtr& userActionType, const ConfigNodePtr& settings);
        ~HarvestCommand();

        void execute(const SharedManagerPtr& shared) override;
        IdPtr getCommandType() const override;
        void undo(const SharedManagerPtr& shared) override;

    private:
        const std::string name = "frts::HarvestCommand";

        IdPtr commandType;
        IdPtr userActionType;
        ConfigNodePtr settings;

        ActionPtr action;
    };

    /**
     * @brief Create new harvest command.
     * @param commandType The command type.
     * @param userActionType The user action type.
     * @param settings The settings node.
     * @return The command.
     */
    inline CommandPtr makeHarvestCommand(const IdPtr& commandType, const IdPtr& userActionType, const ConfigNodePtr& settings)
    {
        assert(commandType != nullptr);
        assert(userActionType != nullptr);
        assert(settings != nullptr);

        return std::make_shared<HarvestCommand>(commandType, userActionType, settings);
    }
}

#endif // FRTS_HARVESTCOMMAND_H
