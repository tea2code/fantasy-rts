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
        HarvestCommand(IdPtr commandType, IdPtr userActionType, ConfigNodePtr settings);
        ~HarvestCommand();

        void execute(SharedManagerPtr shared) override;
        IdPtr getCommandType() const override;
        void undo(SharedManagerPtr shared) override;

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
    inline CommandPtr makeHarvestCommand(IdPtr commandType, IdPtr userActionType, ConfigNodePtr settings)
    {
        assert(commandType != nullptr);
        assert(userActionType != nullptr);
        assert(settings != nullptr);

        return std::make_shared<HarvestCommand>(commandType, userActionType, settings);
    }
}

#endif // FRTS_HARVESTCOMMAND_H
