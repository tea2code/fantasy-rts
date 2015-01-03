#ifndef FRTS_DROPBUILDER_H
#define FRTS_DROPBUILDER_H

#include <entity/ComponentBuilder.h>


namespace frts
{
    /**
     * @brief Builder for drop components.
     */
    class DropBuilder : public ComponentBuilder
    {
    public:
        DropBuilder();

        ComponentPtr build(SharedManagerPtr shared) override;
        ComponentPtr build(SharedManagerPtr shared, ConfigNodePtr node) override;
    };

    /**
     * @brief Create new drop builder.
     * @return The component builder.
     */
    inline ComponentBuilderPtr makeDropBuilder()
    {
        return std::make_shared<DropBuilder>();
    }
}

#endif // FRTS_DROPBUILDER_H
