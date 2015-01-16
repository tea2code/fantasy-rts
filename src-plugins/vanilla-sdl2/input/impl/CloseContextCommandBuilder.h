#ifndef FRTS_CLOSECONTEXTCOMMANDBUILDER_H
#define FRTS_CLOSECONTEXTCOMMANDBUILDER_H

#include <frts/vanillacommand>


namespace frts
{
    class CloseContextCommandBuilder : public CommandBuilder
    {
    public:
        /**
         * @param commandType The command type.
         */
        CloseContextCommandBuilder(const IdPtr& commandType);
        ~CloseContextCommandBuilder();

        CommandPtr build(const SharedManagerPtr& shared) override;

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new CloseContextCommandBuilder.
     * @param commandType The command type.
     * @return The command builder.
     */
    inline CommandBuilderPtr makeCloseContextCommandBuilder(const IdPtr& commandType)
    {
        return std::make_shared<CloseContextCommandBuilder>(commandType);
    }
}

#endif // FRTS_CLOSECONTEXTCOMMANDBUILDER_H
