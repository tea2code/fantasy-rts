#ifndef FRTS_COMMAND_H
#define FRTS_COMMAND_H

#include <frts/shared>

#include <memory>


namespace frts
{
    class Command;

    /**
     * @brief Pointer to Command.
     */
    using CommandPtr = std::shared_ptr<Command>;

    /**
     * @brief Interface for commands. Allows implementation of the command
     *        pattern.
     */
    class Command
    {
    public:
        virtual ~Command() {}

        /**
         * @brief Execute the command.
         * @param shared The shared manager.
         */
        virtual void execute(SharedManagerPtr shared) = 0;

        /**
         * @brief Undo the execution of this command.
         * @param shared The shared manager.
         */
        virtual void undo(SharedManagerPtr shared) = 0;
    };
}

#endif // FRTS_COMMAND_H
