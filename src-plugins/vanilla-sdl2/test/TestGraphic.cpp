#include <catch.hpp>

#include <graphic/impl/RenderableImpl.h>

#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>


TEST_CASE("Renderable.", "[graphic]")
{
    frts::LogPtr log = std::make_shared<frts::NoLog>();
    frts::SharedManagerPtr shared = frts::makeSharedManager(log);

    frts::RenderablePtr component = frts::makeRenderable(shared->makeId(frts::Renderable::componentType()));
    component->addSprite(shared->makeId("sprite1"));
    component->setSpriteIndex(3);

    REQUIRE(component->getSprite(0) == shared->makeId("sprite1"));
    REQUIRE(component->getSpriteIndex() == 3);
}
