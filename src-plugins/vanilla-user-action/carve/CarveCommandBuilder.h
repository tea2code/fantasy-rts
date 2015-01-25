#ifndef FRTS_CARVECOMMANDBUILDER_H
#define FRTS_CARVECOMMANDBUILDER_H

#include <main/UserActionCommandBuilder.h>


namespace frts
{
    class CarveCommandBuilder : public UserActionCommandBuilder
    {
    public:
        /**
         * @param commandType The command type.
         * @param userActionType The user action type.
         */
        CarveCommandBuilder(const IdPtr& commandType, const IdPtr& userActionType);
        ~CarveCommandBuilder();

        CommandPtr build(const SharedManagerPtr& shared) override;
        void setSettings(const ConfigNodePtr& node) override;

    private:
        IdPtr commandType;
        IdPtr userActionType;
        ConfigNodePtr node;
    };

    /**
     * @brief Create new carve command builder.
     * @param commandType The command type.
     * @param userActionType The user action type.
     * @return The command builder.
     */
    inline UserActionCommandBuilderPtr makeCarveCommandBuilder(const IdPtr& commandType, const IdPtr& userActionType)
    {
        assert(commandType != nullptr);
        assert(userActionType != nullptr);

        return std::make_shared<CarveCommandBuilder>(commandType, userActionType);
    }
}

#endif // FRTS_CARVECOMMANDBUILDER_H
