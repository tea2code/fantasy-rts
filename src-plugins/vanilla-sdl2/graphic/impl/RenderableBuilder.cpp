#include "RenderableBuilder.h"

#include "RenderableImpl.h"


frts::RenderableBuilder::RenderableBuilder()
{
}

frts::ComponentPtr frts::RenderableBuilder::build(SharedManagerPtr shared)
{
    IdPtr id = shared->makeId(Renderable::componentType());
    return makeRenderable(id);
}

frts::ComponentPtr frts::RenderableBuilder::build(SharedManagerPtr shared, ConfigNodePtr node)
{
    RenderablePtr component = std::static_pointer_cast<Renderable>(build(shared));
    IdPtr id = shared->makeId(node->getString("sprite"));
    component->addSprite(id);
    return component;
}
