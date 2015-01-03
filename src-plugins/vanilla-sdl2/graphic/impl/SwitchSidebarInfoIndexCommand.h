#ifndef FRTS_SWITCHSIDEBARINFOINDEXCOMMAND_H
#define FRTS_SWITCHSIDEBARINFOINDEXCOMMAND_H

#include <frts/vanillacommand>


namespace frts
{
    /**
     * @brief The SwitchSidebarInfoIndexCommand class
     */
    class SwitchSidebarInfoIndexCommand : public Command
    {
    public:
        /**
         * @param commandType The command type.
         * @param stepSize The step size.
         */
        SwitchSidebarInfoIndexCommand(IdPtr commandType, int stepSize);

        void execute(SharedManagerPtr shared) override;
        IdPtr getCommandType() const override;
        void undo(SharedManagerPtr shared) override;

    private:
        IdPtr commandType;
        int stepSize = 0;
    };

    /**
     * @brief Create new switch sidebar info index command.
     * @param commandType The command type.
     * @return The command.
     */
    inline CommandPtr makeSwitchSidebarInfoIndexCommand(IdPtr commandType, int stepSize)
    {
        assert(commandType != nullptr);
        assert(stepSize != 0);

        return std::make_shared<SwitchSidebarInfoIndexCommand>(commandType, stepSize);
    }
}

#endif // FRTS_SWITCHSIDEBARINFOINDEXCOMMAND_H
