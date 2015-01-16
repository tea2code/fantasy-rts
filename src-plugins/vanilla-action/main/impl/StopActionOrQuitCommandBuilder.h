#ifndef FRTS_STOPACTIONORQUITCOMMANDBUILDER_H
#define FRTS_STOPACTIONORQUITCOMMANDBUILDER_H

#include <frts/vanillacommand>


namespace frts
{
    class StopActionOrQuitCommandBuilder : public CommandBuilder
    {
    public:
        StopActionOrQuitCommandBuilder(const IdPtr& commandType);
        ~StopActionOrQuitCommandBuilder();

        CommandPtr build(const SharedManagerPtr& shared) override;

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new StopActionOrQuitCommandBuilder.
     * @param commandType The command type.
     * @return The command builder.
     */
    inline CommandBuilderPtr makeStopActionOrQuitCommandBuilder(const IdPtr& commandType)
    {
        assert(commandType != nullptr);

        return std::make_shared<StopActionOrQuitCommandBuilder>(commandType);
    }
}

#endif // FRTS_STOPACTIONORQUITCOMMANDBUILDER_H
