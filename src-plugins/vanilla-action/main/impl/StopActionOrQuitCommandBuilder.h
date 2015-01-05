#ifndef FRTS_STOPACTIONORQUITCOMMANDBUILDER_H
#define FRTS_STOPACTIONORQUITCOMMANDBUILDER_H

#include <frts/vanillacommand>


namespace frts
{
    class StopActionOrQuitCommandBuilder : public CommandBuilder
    {
    public:
        StopActionOrQuitCommandBuilder(IdPtr commandType);
        ~StopActionOrQuitCommandBuilder();

        CommandPtr build(SharedManagerPtr shared) override;

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new StopActionOrQuitCommandBuilder.
     * @param commandType The command type.
     * @return The command builder.
     */
    inline CommandBuilderPtr makeStopActionOrQuitCommandBuilder(IdPtr commandType)
    {
        assert(commandType != nullptr);

        return std::make_shared<StopActionOrQuitCommandBuilder>(commandType);
    }
}

#endif // FRTS_STOPACTIONORQUITCOMMANDBUILDER_H
