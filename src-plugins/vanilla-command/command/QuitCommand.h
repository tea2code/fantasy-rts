#ifndef FRTS_QUITCOMMAND_H
#define FRTS_QUITCOMMAND_H

#include <main/Command.h>

#include <memory>


namespace frts
{
    /**
     * @brief This command quits the application.
     */
    class QuitCommand : public Command
    {
    public:
        /**
         * @param commandType The command type.
         */
        QuitCommand(IdPtr commandType);

        void execute(SharedManagerPtr shared) override;
        IdPtr getCommandType() const override;
        void undo(SharedManagerPtr shared) override;

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new quit command.
     * @param commandType The command type.
     * @return The command.
     */
    inline CommandPtr makeQuitCommand(IdPtr commandType)
    {
        assert(commandType != nullptr);
        return std::make_shared<QuitCommand>(commandType);
    }
}

#endif // FRTS_QUITCOMMAND_H
