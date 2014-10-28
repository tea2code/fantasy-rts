#include <catch.hpp>

#include <graphic/impl/RenderableImpl.h>
#include <graphic/impl/Sprite.h>
#include <graphic/impl/SpritePoint.h>
#include <main/Sdl2Ids.h>

#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>

#include <vector>


TEST_CASE("Renderable.", "[graphic]")
{
    frts::LogPtr log = std::make_shared<frts::NoLog>();
    frts::SharedManagerPtr shared = frts::makeSharedManager(log);

    frts::RenderablePtr component = frts::makeRenderable(shared->makeId(frts::Sdl2Ids::renderable()));
    component->setSprite(shared->makeId("sprite1"));

    REQUIRE_FALSE(component->isSpriteIndexSet());

    component->setSpriteIndex(3);

    REQUIRE(component->getSprite() == shared->makeId("sprite1"));
    REQUIRE(component->getSpriteIndex() == 3);
    REQUIRE(component->isSpriteIndexSet());
}

TEST_CASE("Sprite.", "[graphic]")
{
    frts::LogPtr log = std::make_shared<frts::NoLog>();
    frts::SharedManagerPtr shared = frts::makeSharedManager(log);

    frts::IdPtr image = shared->makeId("image");
    std::vector<frts::SpritePoint> spritePoints = {frts::SpritePoint(1, 2, 0.99)};
    frts::Sprite sprite(image, 10, 20, spritePoints);

    REQUIRE(sprite.getHeight() == 10);
    REQUIRE(sprite.getImage() == image);
    REQUIRE(sprite.getWidth() == 20);
    REQUIRE(sprite.getX() == 1);
    REQUIRE(sprite.getY() == 2);
}
