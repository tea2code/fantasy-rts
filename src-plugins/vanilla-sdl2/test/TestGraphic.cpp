#include <catch.hpp>

#include <graphic/impl/MoveCursorCommand.h>
#include <graphic/impl/MoveCursorCommandBuilder.h>
#include <graphic/impl/MoveScreenCommand.h>
#include <graphic/impl/MoveScreenCommandBuilder.h>
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
    gd->setScreenOffsetX(8);
    gd->setScreenOffsetY(9);
    gd->setScreenOffsetStepX(10);
    gd->setScreenOffsetStepY(11);
    gd->setSidebarWidth(12);

    frts::GraphicData::ScreenArea sidebarArea;
    sidebarArea.x = 1;
    sidebarArea.y = 2;
    sidebarArea.height = 3;
    sidebarArea.width = 4;
    gd->setSidebarArea(sidebarArea);

    frts::GraphicData::ScreenArea mapArea;
    mapArea.x = 5;
    mapArea.y = 6;
    mapArea.height = 7;
    mapArea.width = 8;
    gd->setMapArea(mapArea);

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
    REQUIRE(gd->getScreenOffsetX() == 8);
    REQUIRE(gd->getScreenOffsetY() == 9);
    REQUIRE(gd->getScreenOffsetStepX() == 10);
    REQUIRE(gd->getScreenOffsetStepY() == 11);
    REQUIRE(gd->getSidebarWidth() == 12);

    REQUIRE(gd->getSidebarArea().x == 1);
    REQUIRE(gd->getSidebarArea().y == 2);
    REQUIRE(gd->getSidebarArea().height == 3);
    REQUIRE(gd->getSidebarArea().width == 4);

    REQUIRE(gd->getMapArea().x == 5);
    REQUIRE(gd->getMapArea().y == 6);
    REQUIRE(gd->getMapArea().height == 7);
    REQUIRE(gd->getMapArea().width == 8);
}

TEST_CASE("GraphicData.ScreenArea", "[graphic]")
{
    // x x x x x
    // x a a a x
    // x a a a x
    // x a a a x
    // x x x x x
    frts::GraphicData::ScreenArea a(1, 1, 3, 3);
    frts::GraphicData::pixel size = 5;
    for (frts::GraphicData::pixel x = 0; x < size; ++x)
    {
        for (frts::GraphicData::pixel y = 0; y < size; ++y)
        {
            if (x == 0 || x == size - 1 || y == 0 || y == size - 1)
            {
                REQUIRE_FALSE(a.isPixelInRect(x, y));
            }
            else
            {
                REQUIRE(a.isPixelInRect(x, y));
            }
        }
    }
}

TEST_CASE("Renderable.", "[graphic]")
{
    auto log = std::make_shared<frts::NoLog>();
    auto shared = frts::makeSharedManager(log);

    auto component = frts::makeRenderable(shared->makeId(frts::Sdl2Ids::renderable()));
    component->setSprite(shared->makeId("sprite1"));

    REQUIRE_FALSE(component->isSpriteIndexSet());

    component->setSpriteIndex(3);
    component->setTransparency(4);

    REQUIRE(component->getSprite() == shared->makeId("sprite1"));
    REQUIRE(component->getSpriteIndex() == 3);
    REQUIRE(component->isSpriteIndexSet());
    REQUIRE(component->getTransparency() == 4);
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

// The following test case has a huge dependency on vanilla-model.
//TEST_CASE("MoveScreenCommand.", "[graphic]")
//{
//    auto log = frts::makeNoLog();
//    auto shared = frts::makeSharedManager(log);

//    auto gd = frts::makeGraphicData();
//    shared->setDataValue(shared->makeId(frts::Sdl2Ids::graphicData()), gd);
//    auto mf = frts::makeModelFactory();
//    mf->createData(shared);
//    mf->init(shared);
//    mf->init(shared);
//    shared->setUtility(shared->makeId(frts::ModelIds::modelFactory()), mf);
//    auto rc = frts::getDataValue<frts::ModelData>(shared, frts::ModelIds::modelData());

//    gd->setRenderEverything(false);
//    gd->setScreenHeight(20);
//    gd->setScreenOffsetX(0);
//    gd->setScreenOffsetY(0);
//    gd->setScreenWidth(20);
//    gd->setTileHeight(10);
//    gd->setTileWidth(10);
//    gd->setZLevel(0);
//    rc->setMapSizeX(3);
//    rc->setMapSizeY(4);

//    auto commandId = shared->makeId("command.id");

//    auto builderWest = frts::makeMoveScreenCommandBuilder(commandId, 2, 0, 0);
//    auto commandWest = builderWest->build(shared);
//    REQUIRE(commandWest != nullptr);

//    auto builderEast = frts::makeMoveScreenCommandBuilder(commandId, -2, 0, 0);
//    auto commandEast = builderEast->build(shared);
//    REQUIRE(commandEast != nullptr);

//    auto builderNorth = frts::makeMoveScreenCommandBuilder(commandId, 0, 2, 0);
//    auto commandNorth = builderNorth->build(shared);
//    REQUIRE(commandNorth != nullptr);

//    auto builderSouth= frts::makeMoveScreenCommandBuilder(commandId, 0, -2, 0);
//    auto commandSouth = builderSouth->build(shared);
//    REQUIRE(commandSouth != nullptr);

//    auto builderUp = frts::makeMoveScreenCommandBuilder(commandId, 0, 0, 1);
//    auto commandUp = builderUp->build(shared);
//    REQUIRE(commandUp != nullptr);

//    auto builderDown = frts::makeMoveScreenCommandBuilder(commandId, 0, 0, -1);
//    auto commandDown = builderDown->build(shared);
//    REQUIRE(commandDown != nullptr);

//    commandWest->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 0);
//    REQUIRE(gd->getScreenOffsetY() == 0);
//    REQUIRE(gd->getZLevel() == 0);
//    REQUIRE_FALSE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandWest->undo(shared);
//    REQUIRE(gd->getScreenOffsetX() == 0);
//    REQUIRE(gd->getScreenOffsetY() == 0);
//    REQUIRE(gd->getZLevel() == 0);
//    REQUIRE_FALSE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandNorth->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 0);
//    REQUIRE(gd->getScreenOffsetY() == 0);
//    REQUIRE(gd->getZLevel() == 0);
//    REQUIRE_FALSE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandEast->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 0);
//    REQUIRE(gd->getZLevel() == 0);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandEast->undo(shared);
//    REQUIRE(gd->getScreenOffsetX() == 0);
//    REQUIRE(gd->getScreenOffsetY() == 0);
//    REQUIRE(gd->getZLevel() == 0);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandEast->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 0);
//    REQUIRE(gd->getZLevel() == 0);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandEast->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 0);
//    REQUIRE(gd->getZLevel() == 0);
//    REQUIRE_FALSE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandNorth->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 0);
//    REQUIRE(gd->getZLevel() == 0);
//    REQUIRE_FALSE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandSouth->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == 0);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandSouth->undo(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 0);
//    REQUIRE(gd->getZLevel() == 0);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandSouth->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == 0);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandSouth->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == 0);
//    REQUIRE_FALSE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandUp->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == 1);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandUp->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == 2);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandUp->undo(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == 1);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandUp->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == 2);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandDown->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == 1);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandDown->undo(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == 2);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandDown->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == 1);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandDown->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == 0);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandDown->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == -1);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandWest->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 0);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == -1);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandWest->undo(shared);
//    REQUIRE(gd->getScreenOffsetX() == 1);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == -1);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandWest->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 0);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == -1);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandNorth->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 0);
//    REQUIRE(gd->getScreenOffsetY() == 0);
//    REQUIRE(gd->getZLevel() == -1);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandNorth->undo(shared);
//    REQUIRE(gd->getScreenOffsetX() == 0);
//    REQUIRE(gd->getScreenOffsetY() == 2);
//    REQUIRE(gd->getZLevel() == -1);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);

//    commandNorth->execute(shared);
//    REQUIRE(gd->getScreenOffsetX() == 0);
//    REQUIRE(gd->getScreenOffsetY() == 0);
//    REQUIRE(gd->getZLevel() == -1);
//    REQUIRE(gd->isRenderEverything());
//    gd->setRenderEverything(false);
//}
