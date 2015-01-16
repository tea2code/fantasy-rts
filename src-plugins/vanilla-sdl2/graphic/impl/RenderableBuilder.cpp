#include "RenderableBuilder.h"

#include "RenderableImpl.h"
#include <main/Sdl2Ids.h>


frts::RenderableBuilder::RenderableBuilder()
{
}

frts::ComponentPtr frts::RenderableBuilder::build(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto id = shared->makeId(Sdl2Ids::renderable());
    return makeRenderable(id);
}

frts::ComponentPtr frts::RenderableBuilder::build(const SharedManagerPtr& shared, const ConfigNodePtr& node)
{
    assert(shared != nullptr);
    assert(node != nullptr);

    auto component = std::static_pointer_cast<Renderable>(build(shared));
    auto id = shared->makeId(node->getString("sprite"));
    component->setSprite(id);
    component->setStacking(node->getBool("stacking", true));
    component->setTransparency(getCastInteger<unsigned int>(node, "transparency", 0));
    return component;
}
