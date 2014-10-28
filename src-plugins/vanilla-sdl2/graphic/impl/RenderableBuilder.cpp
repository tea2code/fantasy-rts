#include "RenderableBuilder.h"

#include "RenderableImpl.h"
#include <main/Sdl2Ids.h>


frts::RenderableBuilder::RenderableBuilder()
{
}

frts::ComponentPtr frts::RenderableBuilder::build(SharedManagerPtr shared)
{
    IdPtr id = shared->makeId(Sdl2Ids::renderable());
    return makeRenderable(id);
}

frts::ComponentPtr frts::RenderableBuilder::build(SharedManagerPtr shared, ConfigNodePtr node)
{
    RenderablePtr component = std::static_pointer_cast<Renderable>(build(shared));
    IdPtr id = shared->makeId(node->getString("sprite"));
    component->setSprite(id);
    return component;
}
