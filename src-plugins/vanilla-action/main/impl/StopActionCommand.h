#ifndef FRTS_STOPACTIONCOMMAND_H
#define FRTS_STOPACTIONCOMMAND_H

#include <frts/vanillacommand>

#include <memory>


namespace frts
{
    /**
     * @brief This command will stop the currently running action.
     */
    class StopActionCommand : public Command
    {
    public:
        StopActionCommand(IdPtr commandType);
        ~StopActionCommand();

        void execute(SharedManagerPtr shared) override;
        IdPtr getCommandType() const override;
        void undo(SharedManagerPtr shared) override;

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new StopActionCommand.
     * @param commandType The command type.
     * @return The command.
     */
    inline CommandPtr makeStopActionCommand(IdPtr commandType)
    {
        assert(commandType != nullptr);

        return std::make_shared<StopActionCommand>(commandType);
    }
}

#endif // FRTS_STOPACTIONCOMMAND_H
