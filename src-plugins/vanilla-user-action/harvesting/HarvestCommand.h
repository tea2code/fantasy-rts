#ifndef FRTS_HARVESTCOMMAND_H
#define FRTS_HARVESTCOMMAND_H

#include <frts/vanillacommand>


namespace frts
{
    class HarvestCommand : public Command
    {
    public:
        /**
         * @param commandType The command type.
         * @param settings The settings node.
         */
        HarvestCommand(IdPtr commandType, ConfigNodePtr settings);
        ~HarvestCommand();

        void execute(SharedManagerPtr shared) override;
        IdPtr getCommandType() const override;
        void undo(SharedManagerPtr shared) override;

    private:
        const std::string name = "frts::HarvestCommand";

        IdPtr commandType;
    };

    /**
     * @brief Create new harvest command.
     * @param commandType The command type.
     * @param settings The settings node.
     * @return The command.
     */
    inline CommandPtr makeHarvestCommand(IdPtr commandType, ConfigNodePtr settings)
    {
        assert(commandType != nullptr);
        assert(settings != nullptr);

        return std::make_shared<HarvestCommand>(commandType, settings);
    }
}

#endif // FRTS_HARVESTCOMMAND_H
