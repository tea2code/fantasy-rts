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
        SelectCommand(IdPtr commandType);
        ~SelectCommand();

        void execute(SharedManagerPtr shared) override;
        IdPtr getCommandType() const override;
        void undo(SharedManagerPtr shared) override;

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new select command.
     * @param commandType The command type.
     * @return The command.
     */
    inline CommandPtr makeSelectCommand(IdPtr commandType)
    {
        assert(commandType != nullptr);

        return std::make_shared<SelectCommand>(commandType);
    }
}

#endif // FRTS_SELECTCOMMAND_H
