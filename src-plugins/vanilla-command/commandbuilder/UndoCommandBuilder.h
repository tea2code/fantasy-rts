#ifndef FRTS_UNDOCOMMANDBUILDER_H
#define FRTS_UNDOCOMMANDBUILDER_H

#include <main/CommandBuilder.h>

#include <memory>


namespace frts
{
    /**
     * @brief Builder for undo command
     */
    class UndoCommandBuilder : public CommandBuilder
    {
    public:
        /**
         * @param commandType The command type.
         */
        UndoCommandBuilder(const IdPtr& commandType);

        CommandPtr build(const SharedManagerPtr& shared) override;

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new quit command builder.
     * @param commandType The command type.
     * @return The command builder.
     */
    inline CommandBuilderPtr makeUndoCommandBuilder(const IdPtr& commandType)
    {
        assert(commandType != nullptr);
        return std::make_shared<UndoCommandBuilder>(commandType);
    }
}

#endif // FRTS_UNDOCOMMANDBUILDER_H
