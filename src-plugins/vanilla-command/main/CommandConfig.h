#ifndef FRTS_COMMANDCONFIG_H
#define FRTS_COMMANDCONFIG_H

#include <frts/shared>

#include <memory>
#include <unordered_set>


namespace frts
{
    class CommandConfig;

    /**
     * @brief Pointer to CommandConfig.
     */
    using CommandConfigPtr = std::shared_ptr<CommandConfig>;

    /**
     * @brief Stores settings of command plugin.
     */
    class CommandConfig : public DataValue
    {
    public:
        /**
         * @brief Set of ids.
         */
        using IdSet = std::unordered_set<IdPtr, IdHash, IdEqual>;

    public:
        virtual ~CommandConfig() {}

        /**
         * @brief Get a list of commands which should not be undone.
         * @return The command ids.
         */
        virtual IdSet getNotUndoableCommands() const = 0;

        /**
         * @brief Get number of commands which can be undone.
         * @return The number of commands.
         */
        virtual unsigned int getNumUndo() const = 0;

        /**
         * @brief Set the list of commands which should not be undone.
         * @param commands The command ids.
         */
        virtual void setNotUndoableCommands(IdSet commands) = 0;

        /**
         * @brief Set the number of commands which can be undone.
         * @param numUndo The number of commands.
         */
        virtual void setNumUndo(unsigned int numUndo) = 0;
    };
}

#endif // FRTS_COMMANDCONFIG_H
