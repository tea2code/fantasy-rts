#ifndef FRTS_RENDERABLEBUILDER_H
#define FRTS_RENDERABLEBUILDER_H

#include <frts/vanillamodeldev>


namespace frts
{
    class RenderableBuilder : public ComponentBuilder
    {
    public:
        RenderableBuilder();

        ComponentPtr build(const EntityPtr& entity, const SharedManagerPtr& shared) override;
        ComponentPtr build(const EntityPtr& entity, const SharedManagerPtr& shared, const ConfigNodePtr& node) override;
    };

    /**
     * @brief Create new RenderableBuilder.
     * @return The component builder.
     */
    inline ComponentBuilderPtr makeRenderableBuilder()
    {
        return std::make_shared<RenderableBuilder>();
    }
}

#endif // FRTS_RENDERABLEBUILDER_H
