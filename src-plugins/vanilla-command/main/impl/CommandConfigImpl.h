#ifndef FRTS_COMMANDCONFIGIMPL_H
#define FRTS_COMMANDCONFIGIMPL_H

#include <main/CommandConfig.h>
#include <frts/BaseDataValue.h>


namespace frts
{
    class CommandConfigImpl : public BaseDataValue<CommandConfig>
    {
    public:
        CommandConfigImpl();

        IdUnorderedSet getNotUndoableCommands() const override;
        unsigned int getNumUndo() const override;
        void setNotUndoableCommands(const IdUnorderedSet& commands) override;
        void setNumUndo(unsigned int numUndo) override;

    private:
        IdUnorderedSet notUndoableCommands;
        unsigned int numUndo = 0;
    };

    /**
     * @brief Create new CommandConfig.
     * @return The CommandConfig.
     */
    inline CommandConfigPtr makeCommandConfig()
    {
        return std::make_shared<CommandConfigImpl>();
    }
}

#endif // FRTS_COMMANDCONFIGIMPL_H
