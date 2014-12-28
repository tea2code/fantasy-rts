#include "Sdl2Renderer.h"

#include "impl/GraphicDataImpl.h"
#include "impl/GraphicUtility.h"
#include "impl/RenderableBuilder.h"
#include "impl/MoveScreenCommandBuilder.h"
#include "impl/MoveCursorCommandBuilder.h"
#include <main/Sdl2Ids.h>

#include <frts/vanillacommand>

#include <boost/format.hpp>


frts::Sdl2Renderer::Sdl2Renderer()
    : BaseTickable("frts::SDL2Renderer", 1, "frts::SDL2Renderer", 1)
{}

void frts::Sdl2Renderer::checkRequiredData(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateDataValue(getName(), Sdl2Ids::graphicData(), 2, shared);
}

bool frts::Sdl2Renderer::createData(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto gd = makeGraphicData();
    auto id = shared->makeId(Sdl2Ids::graphicData());
    shared->setDataValue(id, gd);

    return false;
}

frts::GraphicDataPtr frts::Sdl2Renderer::graphicData(SharedManagerPtr shared) const
{
    assert(shared != nullptr);

    return getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
}

std::vector<std::string> frts::Sdl2Renderer::getSupportedConfig()
{
    return {"style", "screen", "tile", "region"};
}

bool frts::Sdl2Renderer::init(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto commandFactory = getUtility<CommandFactory>(shared, CommandIds::commandFactory());
    if (!commandFactory->isInitialized())
    {
        return true;
    }

    auto modelFactory = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
    if (!modelFactory->isInitialized())
    {
        return true;
    }

    auto gd = graphicData(shared);

    // Register renderable.
    auto componentId = shared->makeId(Sdl2Ids::renderable());
    auto componentBuilder = makeRenderableBuilder();
    modelFactory->registerComponentBuilder(componentId, componentBuilder);

    // Init cursor position. Must be after registering renderable.
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    auto pos = modelFactory->makePoint(0, 0, 0);
    auto entity = modelFactory->makeEntity(shared->makeId(cursorId), shared);
    gd->setCursor(entity);
    rm->setPos(entity, pos, shared);

    // Init fps manager.
    fpsManager.setNumFpsAvg(gd->getNumFpsAvg());

    // Init drawer
    drawer.init(shared);
    gd->setRenderEverything();

    // Add commands.
    // Move screen.
    {
        const Point::value offsetStepX = screenToRegion(gd->getScreenOffsetStepX(), gd->getTileWidth());
        const Point::value offsetStepY = screenToRegion(gd->getScreenOffsetStepY(), gd->getTileHeight());
        const Point::value offsetStepZ = 1;

        // West
        IdPtr commandId = shared->makeId(Sdl2Ids::moveScreenCommandWest());
        commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, offsetStepX, 0, 0));

        // East
        commandId = shared->makeId(Sdl2Ids::moveScreenCommandEast());
        commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, -offsetStepX, 0, 0));

        // North
        commandId = shared->makeId(Sdl2Ids::moveScreenCommandNorth());
        commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, 0, offsetStepY, 0));

        // South
        commandId = shared->makeId(Sdl2Ids::moveScreenCommandSouth());
        commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, 0, -offsetStepY, 0));

        // Up
        commandId = shared->makeId(Sdl2Ids::moveScreenCommandUp());
        commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, 0, 0, offsetStepZ));

        // Down
        commandId = shared->makeId(Sdl2Ids::moveScreenCommandDown());
        commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, 0, 0, -offsetStepZ));

        // North West
        commandId = shared->makeId(Sdl2Ids::moveScreenCommandNorthWest());
        commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, offsetStepX, offsetStepY, 0));

        // North East
        commandId = shared->makeId(Sdl2Ids::moveScreenCommandNorthEast());
        commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, -offsetStepX, offsetStepY, 0));

        // South East
        commandId = shared->makeId(Sdl2Ids::moveScreenCommandSouthEast());
        commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, -offsetStepX, -offsetStepY, 0));

        // South West
        commandId = shared->makeId(Sdl2Ids::moveScreenCommandSouthWest());
        commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, offsetStepX, -offsetStepY, 0));
    }

    // Move cursor.
    {
        const int cursorStepX = 1;
        const int cursorStepY = 1;

        // West
        IdPtr commandId = shared->makeId(Sdl2Ids::moveCursorCommandWest());
        commandFactory->registerCommandBuilder(commandId, makeMoveCursorCommandBuilder(commandId, cursorStepX, 0, 0));

        // East
        commandId = shared->makeId(Sdl2Ids::moveCursorCommandEast());
        commandFactory->registerCommandBuilder(commandId, makeMoveCursorCommandBuilder(commandId, -cursorStepX, 0, 0));

        // North
        commandId = shared->makeId(Sdl2Ids::moveCursorCommandNorth());
        commandFactory->registerCommandBuilder(commandId, makeMoveCursorCommandBuilder(commandId, 0, cursorStepY, 0));

        // South
        commandId = shared->makeId(Sdl2Ids::moveCursorCommandSouth());
        commandFactory->registerCommandBuilder(commandId, makeMoveCursorCommandBuilder(commandId, 0, -cursorStepY, 0));

        // North West
        commandId = shared->makeId(Sdl2Ids::moveCursorCommandNorthWest());
        commandFactory->registerCommandBuilder(commandId, makeMoveCursorCommandBuilder(commandId, cursorStepX, cursorStepY, 0));

        // North East
        commandId = shared->makeId(Sdl2Ids::moveCursorCommandNorthEast());
        commandFactory->registerCommandBuilder(commandId, makeMoveCursorCommandBuilder(commandId, -cursorStepX, cursorStepY, 0));

        // South East
        commandId = shared->makeId(Sdl2Ids::moveCursorCommandSouthEast());
        commandFactory->registerCommandBuilder(commandId, makeMoveCursorCommandBuilder(commandId, -cursorStepX, -cursorStepY, 0));

        // South West
        commandId = shared->makeId(Sdl2Ids::moveCursorCommandSouthWest());
        commandFactory->registerCommandBuilder(commandId, makeMoveCursorCommandBuilder(commandId, cursorStepX, -cursorStepY, 0));
    }

    isInit = true;
    return false;
}

void frts::Sdl2Renderer::parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared)
{
    assert(node != nullptr);
    assert(shared != nullptr);

    // Graphic Data
    auto gd = graphicData(shared);
    if (key == "screen")
    {
        cursorId = node->getString("cursor", cursorId);
        gd->setMaxFps(node->getInteger("fps", gd->getMaxFps()));
        gd->setNumFpsAvg(node->getInteger("num_fps_avg", gd->getNumFpsAvg()));
        gd->setScreenHeight(node->getInteger("height", gd->getScreenHeight()));
        gd->setScreenTitle(node->getString("title", gd->getScreenTitle()));
        gd->setScreenWidth(node->getInteger("width", gd->getScreenWidth()));
        gd->setScreenOffsetStepX(node->getInteger("screen_move_x", gd->getScreenOffsetStepX()));
        gd->setScreenOffsetStepY(node->getInteger("screen_move_y", gd->getScreenOffsetStepY()));
        gd->setSidebarWidth((node->getInteger("sidebar_width", gd->getSidebarWidth())));
    }

    if (key == "tile")
    {
        gd->setTileHeight(node->getInteger("height", gd->getTileHeight()));
        gd->setTileWidth(node->getInteger("width", gd->getTileWidth()));
    }

    if (key == "region")
    {
        gd->setZLevel(node->getInteger("surface_level", gd->getZLevel()));
    }

    // Drawer
    if (key == "style")
    {
        auto rootNamespace = node->getString("namespace");

        if (node->has("background"))
        {
            auto bgNode = node->getNode("background");
            drawer.setTileBackground(bgNode->getInteger("r"), bgNode->getInteger("g"), bgNode->getInteger("b"));
        }

        if (node->has("images"))
        {
            drawer.setImageConfig(shared, rootNamespace, node->getNode("images"));
        }

        if (node->has("sprites"))
        {
            drawer.setSpriteConfig(shared, rootNamespace, node->getNode("sprites"));
        }
    }
}

void frts::Sdl2Renderer::tick(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto gd = graphicData(shared);
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    // FpsManager
    fpsManager.limitFps(gd->getMaxFps());
    auto fps = fpsManager.calcFps();

    // Drawer
    auto windowsTitle = boost::format(gd->getScreenTitle()) % fps;
    drawer.setWindowTitle(windowsTitle.str());
    drawer.setOffsetX(gd->getScreenOffsetX());
    drawer.setOffsetY(gd->getScreenOffsetY());
    if (gd->isRenderEverything())
    {
//        shared->getLog()->debug(getName(), "Beginning to render everything.");

        drawer.updateScreen(shared, gd->getZLevel(), rm, mf, gd);
        drawer.renderNow(shared);
        gd->setRenderEverything(false);

//        shared->getLog()->debug(getName(), "Finished rendering.");
    }
    else
    {
        auto changedPos = rm->getChangedPos();
        if (!changedPos.empty())
        {
//            auto msg = boost::format("Beginning to render %1% positions.") % changedPos.size();
//            shared->getLog()->debug(getName(), msg.str());

            drawer.updatePositions(shared, changedPos, gd->getZLevel(), rm, mf, gd);
            drawer.renderNow(shared);

//            shared->getLog()->debug(getName(), "Finished rendering.");
        }
    }
}

void frts::Sdl2Renderer::validateData(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    // Graphic Data
    auto gd = graphicData(shared);

    if (cursorId.empty())
    {
        throw DataViolation("Sdl2Renderer: Cursor entity is not set.");
    }

    if (gd->getMaxFps() == 0)
    {
        throw DataViolation("Sdl2Renderer: Maximal frames per second must be greater than zero.");
    }

    if (gd->getNumFpsAvg() == 0)
    {
        throw DataViolation("Sdl2Renderer: Number of frames per second measures for average calculation must be greater than zero.");
    }

    if (gd->getScreenHeight() == 0)
    {
        throw DataViolation("Sdl2Renderer: Screen height must be greater than zero.");
    }

    if (gd->getScreenWidth() == 0)
    {
        throw DataViolation("Sdl2Renderer: Screen width must be greater than zero.");
    }

    if (gd->getScreenOffsetStepX() == 0)
    {
        throw DataViolation("Sdl2Renderer: Screen move width in x-direction must be greater than zero.");
    }

    if (gd->getScreenOffsetStepY() == 0)
    {
        throw DataViolation("Sdl2Renderer: Screen move width in y-direction must be greater than zero.");
    }

    if (gd->getSidebarWidth() == 0)
    {
        throw DataViolation("Sdl2Renderer: Sidebar width must be greater than zero.");
    }

    if (gd->getTileHeight() == 0)
    {
        throw DataViolation("Sdl2Renderer: Tile height must be greater than zero.");
    }

    if (gd->getTileWidth() == 0)
    {
        throw DataViolation("Sdl2Renderer: Tile width must be greater than zero.");
    }

    // Drawer
    drawer.validateData(shared);
}

void frts::Sdl2Renderer::validateModules(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateUtility(getName(), CommandIds::commandFactory(), 1, shared);
    validateUtility(getName(), ModelIds::modelFactory(), 1, shared);
}
