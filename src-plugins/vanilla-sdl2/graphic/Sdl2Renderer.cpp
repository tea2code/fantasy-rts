#include "Sdl2Renderer.h"

#include "impl/GraphicDataImpl.h"
#include "impl/GraphicUtility.h"
#include "impl/RenderableBuilder.h"
#include "impl/MoveScreenCommandBuilder.h"
#include "impl/MoveCursorCommandBuilder.h"
#include "impl/SwitchSidebarInfoIndexCommandBuilder.h"
#include <main/Sdl2Ids.h>

#include <frts/vanillacommand>
#include <frts/vanillaevent>

#include <boost/format.hpp>

#include <algorithm>


frts::Sdl2Renderer::Sdl2Renderer()
    : BaseTickable(Sdl2Ids::sdl2Renderer(), 1, Sdl2Ids::sdl2Renderer(), 1),
      nextFpsLog{fromMilliseconds(0)}
{
    drawer = makeDrawer();
    sidebarDrawer = makeSidebarDrawer();
}

void frts::Sdl2Renderer::checkRequiredData(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    validateDataValue(getName(), Sdl2Ids::graphicData(), 4, shared);
    validateDataValue(getName(), MainIds::mainData(), 2, shared);
}

bool frts::Sdl2Renderer::createData(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = makeGraphicData();
    auto id = shared->makeId(Sdl2Ids::graphicData());
    shared->setDataValue(id, gd);

    return false;
}

std::vector<std::string> frts::Sdl2Renderer::getSupportedConfig()
{
    return {"style", "screen", "tile", "region", "sidebar"};
}

bool frts::Sdl2Renderer::init(const SharedManagerPtr& shared)
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

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());

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

    // Init drawer.
    drawer->init(shared);
    gd->setRenderEverything();

    sidebarDrawer->init(drawer, shared);
    auto em = getUtility<EventManager>(shared, EventIds::eventManager());
    for (auto& type : sidebarDrawer->getSidebarEvents())
    {
        em->subscribe(sidebarDrawer, type);
    }

    // Add commands.
    // Move screen.
    {
        const Point::value offsetStepX = pixelToTilesX(gd->getScreenOffsetStepX(), shared);
        const Point::value offsetStepY = pixelToTilesY(gd->getScreenOffsetStepY(), shared);
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

    // Switch sidebar info index.
    {
        const int stepSize = 1;

        // Plus
        IdPtr commandId = shared->makeId(Sdl2Ids::switchSidebarInfoIndexCommandNext());
        commandFactory->registerCommandBuilder(commandId, makeSwitchSidebarInfoIndexCommandBuilder(commandId, stepSize));

        // Minus
        commandId = shared->makeId(Sdl2Ids::switchSidebarInfoIndexCommandPrevious());
        commandFactory->registerCommandBuilder(commandId, makeSwitchSidebarInfoIndexCommandBuilder(commandId, -stepSize));
    }

    return BaseTickable::init(shared);
}

void frts::Sdl2Renderer::parseConfig(const std::string& key, const ConfigNodePtr& node, const SharedManagerPtr& shared)
{
    assert(node != nullptr);
    assert(shared != nullptr);

    // Graphic Data
    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    if (key == "screen")
    {
        cursorId = node->getString("cursor", cursorId);
        gd->setNumFpsAvg(getCastInteger<unsigned int>(node, "num_fps_avg", gd->getNumFpsAvg()));
        gd->setScreenHeight(getCastInteger<GraphicData::pixel>(node, "height", gd->getScreenHeight()));
        gd->setScreenTitle(node->getString("title", gd->getScreenTitle()));
        gd->setScreenWidth(getCastInteger<GraphicData::pixel>(node, "width", gd->getScreenWidth()));
        gd->setScreenOffsetStepX(getCastInteger<GraphicData::pixel>(node, "screen_move_x", gd->getScreenOffsetStepX()));
        gd->setScreenOffsetStepY(getCastInteger<GraphicData::pixel>(node, "screen_move_y", gd->getScreenOffsetStepY()));
        gd->setSidebarWidth(getCastInteger<GraphicData::pixel>(node, "sidebar_width", gd->getSidebarWidth()));
        gd->setZoom(node->getFloat("start_zoom", gd->getZoom()));

        if (node->has("zoom_levels"))
        {
            auto zoomLevels = node->getFloats("zoom_levels");
            std::sort(zoomLevels.begin(), zoomLevels.end());
            gd->setZoomLevels(zoomLevels);
        }
    }
    else if (key == "tile")
    {
        gd->setTileHeight(getCastInteger<GraphicData::pixel>(node, "height", gd->getTileHeight()));
        gd->setTileWidth(getCastInteger<GraphicData::pixel>(node, "width", gd->getTileWidth()));
    }
    else if (key == "region")
    {
        gd->setZLevel(node->getInteger("surface_level", gd->getZLevel()));
    }
    // Drawer
    else if (key == "style")
    {
        auto rootNamespace = node->getString("namespace");
        if (!rootNamespace.empty())
        {
            rootNamespace += ".";
        }

        if (node->has("background"))
        {
            auto bgNode = node->getNode("background");
            auto r = getCastInteger<std::uint8_t>(bgNode, "r");
            auto g = getCastInteger<std::uint8_t>(bgNode, "g");
            auto b = getCastInteger<std::uint8_t>(bgNode, "b");
            drawer->setTileBackground(r, g, b);
        }

        if (node->has("images"))
        {
            drawer->setImageConfig(shared, rootNamespace, node->getNode("images"));
        }

        if (node->has("sprites"))
        {
            drawer->setSpriteConfig(shared, rootNamespace, node->getNode("sprites"));
        }
    }
    // Sidebar drawer
    else if (key == "sidebar")
    {
        sidebarDrawer->setSidebarConfig(shared, node);
    }
}

void frts::Sdl2Renderer::tick(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto graphicData = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto mainData = getDataValue<MainData>(shared, MainIds::mainData());
    auto modelData = getDataValue<ModelData>(shared, ModelIds::modelData());
    auto regionManager = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    auto modelFactory = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    // Drawers
    bool renderNow = false;
    if (graphicData->isRenderEverything())
    {
        drawer->updateMap(shared, graphicData->getZLevel(), regionManager, modelFactory,
                          graphicData, modelData);
        sidebarDrawer->updateSidebar(shared);

        graphicData->setRenderEverything(false);
        renderNow = true;
    }
    else
    {
        // Map
        auto changedPos = regionManager->getChangedPos();
        if (!changedPos.empty())
        {
            drawer->updatePositions(shared, changedPos, graphicData->getZLevel(), regionManager,
                                    modelFactory, graphicData, modelData);
            renderNow = true;
        }

        // Sidebar
        renderNow = sidebarDrawer->updateEvents(shared) || renderNow;
        renderNow = sidebarDrawer->updateInfo(shared) || renderNow;
    }

    // Render.
    if (renderNow)
    {
        drawer->renderNow(shared);
    }

    // FpsManager
    fpsManager.limitFps(mainData->getDeltaTime());
    auto fps = fpsManager.calcFps();
    auto windowsTitle = boost::format(graphicData->getScreenTitle()) % fps % graphicData->getZoom();
    drawer->setWindowTitle(windowsTitle.str());

    // Log every second the current fps.
    if (shared->getFrame()->getRunTime() >= nextFpsLog)
    {
        auto msg = boost::format(R"(FPS of frame %2%: %1%)") % fps % shared->getFrame()->getNumber();
        shared->getLog()->debug(getName(), msg.str());
        nextFpsLog += fromMilliseconds(1000);
    }
}

void frts::Sdl2Renderer::validateData(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    if (cursorId.empty())
    {
        throw DataViolation("Sdl2Renderer: Cursor entity is not set.");
    }

    // Graphic Data
    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());

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
    drawer->validateData(shared);

    // Sidebar drawer
    sidebarDrawer->validateData(shared);
}

void frts::Sdl2Renderer::validateModules(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    validateUtility(getName(), CommandIds::commandFactory(), 1, shared);
    validateUtility(getName(), ModelIds::modelFactory(), 2, shared);
}
