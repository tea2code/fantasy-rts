#ifndef FRTS_USERACTIONCOMMANDBUILDER
#define FRTS_USERACTIONCOMMANDBUILDER

#include <frts/vanillacommand>

#include <memory>


namespace frts
{
    class UserActionCommandBuilder;

    /**
     * @brief Pointer to UserActionCommandBuilder.
     */
    using UserActionCommandBuilderPtr = std::shared_ptr<UserActionCommandBuilder>;

    /**
     * @brief Adds necessary config accessors to the command builder interface. Only for internal use.
     */
    class UserActionCommandBuilder : public CommandBuilder
    {
    public:
        /**
         * @brief Set the settings node for this command builder.A command builder may assume that
         *        this function is always called before the first call to build().
         * @param node The settings node.
         */
        virtual void setSettings(const ConfigNodePtr& node) = 0;
    };
}

#endif // FRTS_USERACTIONCOMMANDBUILDER

