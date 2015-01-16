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
        CloseContextCommand(const IdPtr& commandType);
        ~CloseContextCommand();

        void execute(const SharedManagerPtr& shared);
        IdPtr getCommandType() const;
        void undo(const SharedManagerPtr& shared);

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new CloseContextCommand.
     * @param commandType The command type.
     * @return The command.
     */
    inline CommandPtr makeCloseContextCommand(const IdPtr& commandType)
    {
        assert(commandType != nullptr);

        return std::make_shared<CloseContextCommand>(commandType);
    }
}

#endif // FRTS_CLOSECONTEXTCOMMAND_H
