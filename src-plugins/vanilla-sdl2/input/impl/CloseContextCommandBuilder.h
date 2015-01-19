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
         * @param resetToDefault If true all contexts are closed else only the current.
         */
        CloseContextCommandBuilder(const IdPtr& commandType, bool resetToDefault);
        ~CloseContextCommandBuilder();

        CommandPtr build(const SharedManagerPtr& shared) override;

    private:
        IdPtr commandType;
        bool resetToDefault;
    };

    /**
     * @brief Create new CloseContextCommandBuilder.
     * @param commandType The command type.
     * @param resetToDefault If true all contexts are closed else only the current.
     * @return The command builder.
     */
    inline CommandBuilderPtr makeCloseContextCommandBuilder(const IdPtr& commandType, bool resetToDefault)
    {
        return std::make_shared<CloseContextCommandBuilder>(commandType, resetToDefault);
    }
}

#endif // FRTS_CLOSECONTEXTCOMMANDBUILDER_H
