#ifndef FRTS_SELECTCOMMAND_H
#define FRTS_SELECTCOMMAND_H

#include <frts/vanillacommand>


namespace frts
{
    class SelectCommand : public Command
    {
    public:
        /**
         * @param commandType The command type.
         */
        SelectCommand(const IdPtr& commandType);
        ~SelectCommand();

        void execute(const SharedManagerPtr& shared) override;
        IdPtr getCommandType() const override;
        void undo(const SharedManagerPtr& shared) override;

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new select command.
     * @param commandType The command type.
     * @return The command.
     */
    inline CommandPtr makeSelectCommand(const IdPtr& commandType)
    {
        assert(commandType != nullptr);

        return std::make_shared<SelectCommand>(commandType);
    }
}

#endif // FRTS_SELECTCOMMAND_H
