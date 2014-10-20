#include <catch.hpp>

#include <graphic/impl/RenderableImpl.h>
#include <graphic/impl/Sprite.h>

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

TEST_CASE("Sprite.", "[graphic]")
{
    frts::LogPtr log = std::make_shared<frts::NoLog>();
    frts::SharedManagerPtr shared = frts::makeSharedManager(log);

    frts::IdPtr image = shared->makeId("image");
    frts::SpritePtr sprite = frts::makeSprite(image, 10, 20, 1, 2, 0.99);

    REQUIRE(sprite->getChance() == Approx(0.99));
    REQUIRE(sprite->getHeight() == 10);
    REQUIRE(sprite->getImage() == image);
    REQUIRE(sprite->getWidth() == 20);
    REQUIRE(sprite->getX() == 1);
    REQUIRE(sprite->getY() == 2);
}
