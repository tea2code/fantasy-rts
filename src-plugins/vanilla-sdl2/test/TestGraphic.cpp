#include <catch.hpp>

#include <graphic/impl/GraphicDataImpl.h>
#include <graphic/impl/RenderableBuilder.h>
#include <graphic/impl/RenderableImpl.h>
#include <graphic/impl/Sprite.h>
#include <graphic/impl/SpritePoint.h>
#include <main/Sdl2Ids.h>

#include <frts/configuration>
#include <log/NoLog.h>
#include <shared/impl/SharedManagerImpl.h>

#include <vector>
#include <unordered_map>


namespace TestGraphic
{
    class RenderableConfig : public frts::ConfigNode
    {
    public:
        Iterator begin() { return Iterator(nullptr); }
        Iterator end() { return Iterator(nullptr); }

        bool getBool(const std::string&) { return false; }
        bool getBool(const std::string&, bool) { return false; }
        std::vector<bool> getBools(const std::string&) { return {}; }

        double getFloat(const std::string&) { return 0.0; }
        double getFloat(const std::string&, double) { return 0.0; }
        std::vector<double> getFloats(const std::string&) { return {}; }

        long getInteger(const std::string&) { return 0; }
        long getInteger(const std::string&, long) { return 0; }
        std::vector<long> getIntegers(const std::string&) { return {}; }

        frts::ConfigNodePtr getNode(const std::string&) { return nullptr; }

        std::string getString(const std::string& key) { return key == "sprite" ? "id.sprite" : ""; }
        std::string getString(const std::string&, const std::string&) { return ""; }
        std::vector<std::string> getStrings(const std::string&) { return {}; }

        bool has(const std::string&) { return false; }

        bool isBool(const std::string&) { return false; }
        bool isFloat(const std::string&) { return false; }
        bool isInteger(const std::string&) { return false; }
        bool isString(const std::string&) { return false; }
    };
}


TEST_CASE("Graphic Data.", "[graphic]")
{
    auto gd = frts::makeGraphicData();

    gd->setMaxFps(1);
    gd->setNumFpsAvg(2);
    gd->setScreenHeight(3);
    gd->setScreenTitle("a");
    gd->setScreenWidth(4);
    gd->setTileHeight(5);
    gd->setTileWidth(6);
    gd->setZLevel(7);

    REQUIRE_FALSE(gd->isRenderEverything());
    gd->setRenderEverything();
    REQUIRE(gd->isRenderEverything());
    gd->setRenderEverything(false);
    REQUIRE_FALSE(gd->isRenderEverything());

    REQUIRE(gd->getMaxFps() == 1);
    REQUIRE(gd->getNumFpsAvg() == 2);
    REQUIRE(gd->getScreenHeight() == 3);
    REQUIRE(gd->getScreenWidth() == 4);
    REQUIRE(gd->getTileHeight() == 5);
    REQUIRE(gd->getTileWidth() == 6);
    REQUIRE(gd->getZLevel() == 7);
    REQUIRE(gd->getScreenTitle() == "a");
}

TEST_CASE("Renderable.", "[graphic]")
{
    auto log = std::make_shared<frts::NoLog>();
    auto shared = frts::makeSharedManager(log);

    auto component = frts::makeRenderable(shared->makeId(frts::Sdl2Ids::renderable()));
    component->setSprite(shared->makeId("sprite1"));

    REQUIRE_FALSE(component->isSpriteIndexSet());

    component->setSpriteIndex(3);

    REQUIRE(component->getSprite() == shared->makeId("sprite1"));
    REQUIRE(component->getSpriteIndex() == 3);
    REQUIRE(component->isSpriteIndexSet());
}

TEST_CASE("Renderable Builder.", "[graphic]")
{
    auto log = std::make_shared<frts::NoLog>();
    auto shared = frts::makeSharedManager(log);

    auto builder = frts::makeRenderableBuilder();

    auto component = builder->build(shared);
    REQUIRE(component != nullptr);

    component = builder->build(shared, std::make_shared<TestGraphic::RenderableConfig>());
    REQUIRE(component != nullptr);
    auto renderable = std::static_pointer_cast<frts::Renderable>(component);
    REQUIRE(renderable->getSprite() == shared->makeId("id.sprite"));
}

TEST_CASE("Sprite.", "[graphic]")
{
    auto log = std::make_shared<frts::NoLog>();
    auto shared = frts::makeSharedManager(log);

    auto image = shared->makeId("image");
    std::vector<frts::SpritePoint> spritePoints = {frts::SpritePoint(1, 2, 0.99)};
    frts::Sprite sprite(image, 10, 20, spritePoints);

    REQUIRE(sprite.getHeight() == 10);
    REQUIRE(sprite.getImage() == image);
    REQUIRE(sprite.getWidth() == 20);
    REQUIRE(sprite.getX() == 1);
    REQUIRE(sprite.getY() == 2);
}
