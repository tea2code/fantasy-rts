#ifndef FRTS_SELECTCOMMANDBUILDER_H
#define FRTS_SELECTCOMMANDBUILDER_H

#include <frts/vanillacommand>


namespace frts
{
    class SelectCommandBuilder : public CommandBuilder
    {
    public:
        /**
         * @param commandType The command type.
         */
        SelectCommandBuilder(IdPtr commandType);
        ~SelectCommandBuilder();

        CommandPtr build(SharedManagerPtr shared) override;

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new select command builder.
     * @param commandType The command type.
     * @return The command builder.
     */
    inline CommandBuilderPtr makeSelectCommandBuilder(IdPtr commandType)
    {
        assert(commandType != nullptr);

        return std::make_shared<SelectCommandBuilder>(commandType);
    }
}

#endif // FRTS_SELECTCOMMANDBUILDER_H
