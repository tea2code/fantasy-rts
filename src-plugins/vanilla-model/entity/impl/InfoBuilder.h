#ifndef FRTS_INFOBUILDER_H
#define FRTS_INFOBUILDER_H

#include <entity/ComponentBuilder.h>

#include <memory>


namespace frts
{
    /**
     * @brief Builder for info component.
     */
    class InfoBuilder : public ComponentBuilder
    {
    public:
        InfoBuilder();

        ComponentPtr build(SharedManagerPtr shared) override;
        ComponentPtr build(SharedManagerPtr shared, ConfigNodePtr node) override;
    };

    /**
     * @brief Create new info builder.
     * @return The component builder.
     */
    inline ComponentBuilderPtr makeInfoBuilder()
    {
        return std::make_shared<InfoBuilder>();
    }
}

#endif // FRTS_INFOBUILDER_H
