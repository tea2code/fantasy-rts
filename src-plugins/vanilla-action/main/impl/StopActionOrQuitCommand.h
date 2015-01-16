#ifndef FRTS_STOPACTIONORQUITCOMMAND_H
#define FRTS_STOPACTIONORQUITCOMMAND_H

#include <frts/vanillacommand>

#include <memory>


namespace frts
{
    /**
     * @brief This command will stop the currently running action. If no action is running
     *        it will quit the application.
     */
    class StopActionOrQuitCommand : public Command
    {
    public:
        StopActionOrQuitCommand(const IdPtr& commandType);
        ~StopActionOrQuitCommand();

        void execute(const SharedManagerPtr& shared) override;
        IdPtr getCommandType() const override;
        void undo(const SharedManagerPtr& shared) override;

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new StopActionOrQuitCommand.
     * @param commandType The command type.
     * @return The command.
     */
    inline CommandPtr makeStopActionOrQuitCommand(const IdPtr& commandType)
    {
        assert(commandType != nullptr);

        return std::make_shared<StopActionOrQuitCommand>(commandType);
    }
}

#endif // FRTS_STOPACTIONORQUITCOMMAND_H
