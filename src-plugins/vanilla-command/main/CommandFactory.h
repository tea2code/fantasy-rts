#ifndef FRTS_COMMANDFACTORY_H
#define FRTS_COMMANDFACTORY_H

#include "Command.h"
#include "CommandBuilder.h"

#include <frts/shared>

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
    class CommandFactory
    {
    public:
        virtual ~CommandFactory() {}

        /**
         * @brief Create a new command.
         * @throws UnknownCommandBuilderError if command builder id is not registered.
         * @param id The id of the command builder.
         * @param shared The shared manager.
         * @return The command.
         */
        virtual CommandPtr makeCommand(IdPtr builderId, SharedManagerPtr shared) = 0;

        /**
         * @brief Register a command builder.
         * @param builderId The id of the command builder.
         * @param commandBuilder The command builder.
         */
        virtual void registerCommandBuilder(IdPtr builderId, CommandBuilderPtr commandBuilder) = 0;
    };
}

#endif // FRTS_COMMANDFACTORY_H
