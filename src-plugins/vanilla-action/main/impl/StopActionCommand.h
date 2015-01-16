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
        StopActionCommand(const IdPtr& commandType);
        ~StopActionCommand();

        void execute(const SharedManagerPtr& shared) override;
        IdPtr getCommandType() const override;
        void undo(const SharedManagerPtr& shared) override;

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new StopActionCommand.
     * @param commandType The command type.
     * @return The command.
     */
    inline CommandPtr makeStopActionCommand(const IdPtr& commandType)
    {
        assert(commandType != nullptr);

        return std::make_shared<StopActionCommand>(commandType);
    }
}

#endif // FRTS_STOPACTIONCOMMAND_H
