#ifndef FRTS_QUITCOMMANDBUILDER_H
#define FRTS_QUITCOMMANDBUILDER_H

#include <main/CommandBuilder.h>

#include <memory>


namespace frts
{
    /**
     * @brief Builder for quit command
     */
    class QuitCommandBuilder : public CommandBuilder
    {
    public:
        /**
         * @param commandType The command type.
         */
        QuitCommandBuilder(const IdPtr& commandType);

        CommandPtr build(const SharedManagerPtr& shared) override;

    private:
        IdPtr commandType;
    };

    /**
     * @brief Create new quit command builder.
     * @param commandType The command type.
     * @return The command builder.
     */
    inline CommandBuilderPtr makeQuitCommandBuilder(const IdPtr& commandType)
    {
        assert(commandType != nullptr);
        return std::make_shared<QuitCommandBuilder>(commandType);
    }
}

#endif // FRTS_QUITCOMMANDBUILDER_H
