#ifndef FRTS_STOPACTIONCOMMANDBUILDER_H
#define FRTS_STOPACTIONCOMMANDBUILDER_H

#include <frts/vanillacommand>


namespace frts
{
    class StopActionCommandBuilder : public CommandBuilder
    {
    public:
        StopActionCommandBuilder(const IdPtr& commandType);
        ~StopActionCommandBuilder();

        CommandPtr build(const SharedManagerPtr& shared) override;

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new StopActionCommandBuilder.
     * @param commandType The command type.
     * @return The command builder.
     */
    inline CommandBuilderPtr makeStopActionCommandBuilder(const IdPtr& commandType)
    {
        assert(commandType != nullptr);

        return std::make_shared<StopActionCommandBuilder>(commandType);
    }
}

#endif // FRTS_STOPACTIONCOMMANDBUILDER_H
