#ifndef FRTS_CARVECOMMAND_H
#define FRTS_CARVECOMMAND_H

#include <frts/vanillaaction>
#include <frts/vanillacommand>


namespace frts
{
    class CarveCommand : public Command
    {
    public:
        /**
         * @param commandType The command type.
         * @param userActionType The user action type.
         * @param settings The settings node.
         */
        CarveCommand(const IdPtr& commandType, const IdPtr& userActionType, const ConfigNodePtr& settings);
        ~CarveCommand();

        void execute(const SharedManagerPtr& shared) override;
        IdPtr getCommandType() const override;
        void undo(const SharedManagerPtr& shared) override;

    private:
        const std::string name = "frts::CarveCommand";

        IdPtr commandType;
        IdPtr userActionType;
        ConfigNodePtr settings;

        ActionPtr action;
    };

    /**
     * @brief Create new carve command.
     * @param commandType The command type.
     * @param userActionType The user action type.
     * @param settings The settings node.
     * @return The command.
     */
    inline CommandPtr makeCarveCommand(const IdPtr& commandType, const IdPtr& userActionType, const ConfigNodePtr& settings)
    {
        assert(commandType != nullptr);
        assert(userActionType != nullptr);
        assert(settings != nullptr);

        return std::make_shared<CarveCommand>(commandType, userActionType, settings);
    }
}

#endif // FRTS_CARVECOMMAND_H
