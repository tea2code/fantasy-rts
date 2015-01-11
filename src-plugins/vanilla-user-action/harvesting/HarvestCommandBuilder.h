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
         */
        HarvestCommandBuilder(IdPtr commandType);
        ~HarvestCommandBuilder();

        CommandPtr build(SharedManagerPtr shared) override;
        void setSettings(ConfigNodePtr node) override;

    private:
        IdPtr commandType;
        ConfigNodePtr node;
    };

    /**
     * @brief Create new harvest command builder.
     * @param commandType The command type.
     * @return The command builder.
     */
    inline UserActionCommandBuilderPtr makeHarvestCommandBuilder(IdPtr commandType)
    {
        assert(commandType != nullptr);

        return std::make_shared<HarvestCommandBuilder>(commandType);
    }
}

#endif // FRTS_HARVESTCOMMANDBUILDER_H
