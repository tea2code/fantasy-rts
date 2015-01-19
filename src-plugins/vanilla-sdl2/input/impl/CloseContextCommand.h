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
         * @param resetToDefault If true all contexts are closed else only the current.
         */
        CloseContextCommand(const IdPtr& commandType, bool resetToDefault);
        ~CloseContextCommand();

        void execute(const SharedManagerPtr& shared);
        IdPtr getCommandType() const;
        void undo(const SharedManagerPtr& shared);

    private:
        IdPtr commandType;
        bool resetToDefault;
    };

    /**
     * @brief Create new CloseContextCommand.
     * @param commandType The command type.
     * @param resetToDefault If true all contexts are closed else only the current.
     * @return The command.
     */
    inline CommandPtr makeCloseContextCommand(const IdPtr& commandType, bool resetToDefault)
    {
        assert(commandType != nullptr);

        return std::make_shared<CloseContextCommand>(commandType, resetToDefault);
    }
}

#endif // FRTS_CLOSECONTEXTCOMMAND_H
