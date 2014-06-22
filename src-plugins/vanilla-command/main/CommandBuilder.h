#ifndef FRTS_COMMANDBUILDER_H
#define FRTS_COMMANDBUILDER_H

#include "Command.h"

#include <frts/shared>

#include <memory>


namespace frts
{
    class CommandBuilder;

    /**
     * @brief Pointer to CommandBuilder.
     */
    using CommandBuilderPtr = std::shared_ptr<CommandBuilder>;

    /**
     * @brief Creates a command.
     */
    class CommandBuilder
    {
    public:
        virtual ~CommandBuilder() {}

        /**
         * @brief Create command.
         * @param shared The shared manager.
         * @return The command.
         */
        virtual CommandPtr build(SharedManagerPtr shared) = 0;
    };
}

#endif // FRTS_COMMANDBUILDER_H
