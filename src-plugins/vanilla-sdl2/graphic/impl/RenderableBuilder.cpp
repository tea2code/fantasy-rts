#include "RenderableBuilder.h"

#include "RenderableImpl.h"
#include <main/Sdl2Ids.h>


frts::RenderableBuilder::RenderableBuilder()
{
}

frts::ComponentPtr frts::RenderableBuilder::build(SharedManagerPtr shared)
{
    auto id = shared->makeId(Sdl2Ids::renderable());
    return makeRenderable(id);
}

frts::ComponentPtr frts::RenderableBuilder::build(SharedManagerPtr shared, ConfigNodePtr node)
{
    auto component = std::static_pointer_cast<Renderable>(build(shared));
    auto id = shared->makeId(node->getString("sprite"));
    component->setSprite(id);
    return component;
}
