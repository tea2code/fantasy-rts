#ifndef FRTS_HARVESTABLEBUILDER_H
#define FRTS_HARVESTABLEBUILDER_H

#include <entity/ComponentBuilder.h>


namespace frts
{
    /**
     * @brief Builder vor harvestable component.
     */
    class HarvestableBuilder : public ComponentBuilder
    {
    public:
        HarvestableBuilder();
        ~HarvestableBuilder();

        ComponentPtr build(SharedManagerPtr shared) override;
        ComponentPtr build(SharedManagerPtr shared, ConfigNodePtr node) override;
    };

    /**
     * @brief Create new harvestable builder.
     * @return The component builder.
     */
    inline ComponentBuilderPtr makeHarvestableBuilder()
    {
        return std::make_shared<HarvestableBuilder>();
    }
}

#endif // FRTS_HARVESTABLEBUILDER_H
