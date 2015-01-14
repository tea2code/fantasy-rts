#ifndef FRTS_CLOSECONTEXTCOMMAND_H
#define FRTS_CLOSECONTEXTCOMMAND_H

#include <frts/vanillacommand>


namespace frts
{
    class CloseContextCommand : public Command
    {
    public:
        /**
         * @param commandType The command type.
         */
        CloseContextCommand(IdPtr commandType);
        ~CloseContextCommand();

        void execute(SharedManagerPtr shared);
        IdPtr getCommandType() const;
        void undo(SharedManagerPtr shared);

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new CloseContextCommand.
     * @param commandType The command type.
     * @return The command.
     */
    inline CommandPtr makeCloseContextCommand(IdPtr commandType)
    {
        assert(commandType != nullptr);

        return std::make_shared<CloseContextCommand>(commandType);
    }
}

#endif // FRTS_CLOSECONTEXTCOMMAND_H
