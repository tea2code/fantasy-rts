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
        QuitCommand();

        void execute(SharedManagerPtr shared);
        void undo(SharedManagerPtr shared);
    };

    /**
     * @brief Create new quit command.
     * @return The command.
     */
    inline CommandPtr makeQuitCommand()
    {
        return std::make_shared<QuitCommand>();
    }
}

#endif // FRTS_QUITCOMMAND_H
