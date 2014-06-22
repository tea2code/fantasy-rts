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
        QuitCommandBuilder();

        CommandPtr build(SharedManagerPtr shared) override;
    };

    /**
     * @brief Create new quit command builder.
     * @return The command builder.
     */
    inline CommandBuilderPtr makeQuitCommandBuilder()
    {
        return std::make_shared<QuitCommandBuilder>();
    }
}

#endif // FRTS_QUITCOMMANDBUILDER_H
