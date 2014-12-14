#ifndef FRTS_COMMANDCONFIGIMPL_H
#define FRTS_COMMANDCONFIGIMPL_H

#include <main/CommandConfig.h>


namespace frts
{
    class CommandConfigImpl : public CommandConfig
    {
    public:
        CommandConfigImpl();

        std::string getName() const override;
        IdSet getNotUndoableCommands() const override;
        unsigned int getNumUndo() const override;
        void setNotUndoableCommands(IdSet commands) override;
        void setNumUndo(unsigned int numUndo) override;
        std::string getTypeName() const override;
        int getTypeVersion() const override;
        int getVersion() const override;

    private:
        IdSet notUndoableCommands;
        int numUndo = 0;
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
