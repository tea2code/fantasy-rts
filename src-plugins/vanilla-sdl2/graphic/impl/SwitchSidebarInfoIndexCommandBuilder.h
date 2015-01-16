#ifndef FRTS_SWITCHSIDEBARINFOINDEXCOMMANDBUILDER_H
#define FRTS_SWITCHSIDEBARINFOINDEXCOMMANDBUILDER_H

#include <frts/vanillacommand>


namespace frts
{
    /**
     * @brief Builder for SwitchSidebarInfoIndexCommand.
     */
    class SwitchSidebarInfoIndexCommandBuilder : public CommandBuilder
    {
    public:
        /**
         * @param commandType The command type.
         * @param stepSize The step size.
         */
        SwitchSidebarInfoIndexCommandBuilder(const IdPtr& commandType, int stepSize);

        CommandPtr build(const SharedManagerPtr& shared) override;

    private:
        IdPtr commandType;
        int stepSize = 0;
    };

    /**
     * @brief Create new switch sidebar info index command builder.
     * @param commandType The command type.
     * @return The command.
     */
    inline CommandBuilderPtr makeSwitchSidebarInfoIndexCommandBuilder(const IdPtr& commandType, int stepSize)
    {
        assert(commandType != nullptr);
        assert(stepSize != 0);

        return std::make_shared<SwitchSidebarInfoIndexCommandBuilder>(commandType, stepSize);
    }
}

#endif // FRTS_SWITCHSIDEBARINFOINDEXCOMMANDBUILDER_H
