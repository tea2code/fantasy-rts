#ifndef FRTS_HARVESTCOMMANDBUILDER_H
#define FRTS_HARVESTCOMMANDBUILDER_H

#include <main/UserActionCommandBuilder.h>


namespace frts
{
    class HarvestCommandBuilder : public UserActionCommandBuilder
    {
    public:
        /**
         * @param commandType The command type.
         * @param userActionType The user action type.
         */
        HarvestCommandBuilder(IdPtr commandType, IdPtr userActionType);
        ~HarvestCommandBuilder();

        CommandPtr build(SharedManagerPtr shared) override;
        void setSettings(ConfigNodePtr node) override;

    private:
        IdPtr commandType;
        IdPtr userActionType;
        ConfigNodePtr node;
    };

    /**
     * @brief Create new harvest command builder.
     * @param commandType The command type.
     * @param userActionType The user action type.
     * @return The command builder.
     */
    inline UserActionCommandBuilderPtr makeHarvestCommandBuilder(IdPtr commandType, IdPtr userActionType)
    {
        assert(commandType != nullptr);
        assert(userActionType != nullptr);

        return std::make_shared<HarvestCommandBuilder>(commandType, userActionType);
    }
}

#endif // FRTS_HARVESTCOMMANDBUILDER_H
