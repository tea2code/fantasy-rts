#ifndef FRTS_UNDOCOMMAND_H
#define FRTS_UNDOCOMMAND_H

#include <main/Command.h>

#include <memory>


namespace frts
{
    /**
     * @brief This command undos the last executed command.
     */
    class UndoCommand : public Command
    {
    public:
        /**
         * @param commandType The command type.
         */
        UndoCommand(const IdPtr& commandType);

        void execute(const SharedManagerPtr& shared) override;
        IdPtr getCommandType() const override;
        void undo(const SharedManagerPtr& shared) override;

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new undo command.
     * @param commandType The command type.
     * @return The command.
     */
    inline CommandPtr makeUndoCommand(const IdPtr& commandType)
    {
        assert(commandType != nullptr);
        return std::make_shared<UndoCommand>(commandType);
    }
}

#endif // FRTS_UNDOCOMMAND_H
