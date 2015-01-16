#ifndef FRTS_COMMANDFACTORY_H
#define FRTS_COMMANDFACTORY_H

#include "Command.h"
#include "CommandBuilder.h"

#include <frts/shared>
#include <frts/module>

#include <memory>


namespace frts
{
    class CommandFactory;

    /**
     * @brief Pointer to CommandFactory.
     */
    using CommandFactoryPtr = std::shared_ptr<CommandFactory>;

    /**
     * @brief Interface for command factory. Allows registration and creation
     *        of new command instances.
     */
    class CommandFactory : public Utility
    {
    public:
        virtual ~CommandFactory() {}

        /**
         * @brief Add a command to the undo list.
         * @param command The command.
         * @param shared The shared manager.
         */
        virtual void addToUndo(const CommandPtr& command, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Create a new command.
         * @throws UnknownCommandBuilderError if command builder id is not registered.
         * @param id The id of the command builder.
         * @param shared The shared manager.
         * @return The command.
         */
        virtual CommandPtr makeCommand(const IdPtr& builderId, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Register a command builder.
         * @param builderId The id of the command builder.
         * @param commandBuilder The command builder.
         */
        virtual void registerCommandBuilder(const IdPtr& builderId, const CommandBuilderPtr& builder) = 0;

        /**
         * @brief Executes undo for the last command.
         * @param shared The shared manager.
         */
        virtual void undoLastCommand(const SharedManagerPtr& shared) = 0;
    };
}

#endif // FRTS_COMMANDFACTORY_H
