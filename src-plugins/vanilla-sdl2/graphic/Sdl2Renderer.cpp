#include "Sdl2Renderer.h"

#include "impl/GraphicDataImpl.h"
#include "impl/RenderableBuilder.h"
#include "impl/MoveScreenCommandBuilder.h"
#include <main/Sdl2Ids.h>

#include <frts/vanillacommand>

#include <boost/format.hpp>


frts::Sdl2Renderer::Sdl2Renderer()
    : BaseTickable("frts::SDL2Renderer", 1, "frts::SDL2Renderer", 1)
{}

bool frts::Sdl2Renderer::createData(SharedManagerPtr shared)
{
    auto gd = makeGraphicData();
    auto id = shared->makeId(Sdl2Ids::graphicData());
    shared->setDataValue(id, gd);

    return false;
}

frts::GraphicDataPtr frts::Sdl2Renderer::graphicData(SharedManagerPtr shared) const
{
    return getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
}

std::vector<std::string> frts::Sdl2Renderer::getSupportedConfig()
{
    return {"style", "screen", "tile"};
}

bool frts::Sdl2Renderer::init(SharedManagerPtr shared)
{
    auto gd = graphicData(shared);

    // Init fps manager.
    fpsManager.setNumFpsAvg(gd->getNumFpsAvg());

    // Register renderable.
    auto id = shared->makeId(ModelIds::modelFactory());
    auto modelFactory = std::static_pointer_cast<ModelFactory>(shared->getUtility(id));
    auto componentId = shared->makeId(Sdl2Ids::renderable());
    auto componentBuilder = makeRenderableBuilder();
    modelFactory->registerComponentBuilder(componentId, componentBuilder);

    // Init drawer
    drawer.init(shared);
    gd->setRenderEverything();

    // Add commands.
    auto commandFactory = getUtility<CommandFactory>(shared, CommandIds::commandFactory());

    const int offsetStepX = (gd->getScreenOffsetStepX() / gd->getTileWidth());
    const int offsetStepY = (gd->getScreenOffsetStepY() / gd->getTileHeight());
    const int offsetStepZ = 1;

    // West
    IdPtr commandId = shared->makeId(Sdl2Ids::moveCommandWest());
    commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, offsetStepX, 0, 0));

    // East
    commandId = shared->makeId(Sdl2Ids::moveCommandEast());
    commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, -offsetStepX, 0, 0));

    // North
    commandId = shared->makeId(Sdl2Ids::moveCommandNorth());
    commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, 0, offsetStepY, 0));

    // South
    commandId = shared->makeId(Sdl2Ids::moveCommandSouth());
    commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, 0, -offsetStepY, 0));

    // Up
    commandId = shared->makeId(Sdl2Ids::moveCommandUp());
    commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, 0, 0, offsetStepZ));

    // Down
    commandId = shared->makeId(Sdl2Ids::moveCommandDown());
    commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, 0, 0, -offsetStepZ));

    // North West
    commandId = shared->makeId(Sdl2Ids::moveCommandNorthWest());
    commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, offsetStepX, offsetStepY, 0));

    // North East
    commandId = shared->makeId(Sdl2Ids::moveCommandNorthEast());
    commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, -offsetStepX, offsetStepY, 0));

    // South East
    commandId = shared->makeId(Sdl2Ids::moveCommandSouthEast());
    commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, -offsetStepX, -offsetStepY, 0));

    // South West
    commandId = shared->makeId(Sdl2Ids::moveCommandSouthWest());
    commandFactory->registerCommandBuilder(commandId, makeMoveScreenCommandBuilder(commandId, offsetStepX, -offsetStepY, 0));

    return false;
}

void frts::Sdl2Renderer::parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared)
{
    // Graphic Data
    auto gd = graphicData(shared);
    if (key == "screen")
    {
        gd->setMaxFps(node->getInteger("fps", gd->getMaxFps()));
        gd->setNumFpsAvg(node->getInteger("num_fps_avg", gd->getNumFpsAvg()));
        gd->setScreenHeight(node->getInteger("height", gd->getScreenHeight()));
        gd->setScreenTitle(node->getString("title", gd->getScreenTitle()));
        gd->setScreenWidth(node->getInteger("width", gd->getScreenWidth()));
        gd->setScreenOffsetStepX(node->getInteger("screen_move_x", gd->getScreenOffsetStepX()));
        gd->setScreenOffsetStepY(node->getInteger("screen_move_y", gd->getScreenOffsetStepY()));
    }

    if (key == "tile")
    {
        gd->setTileHeight(node->getInteger("height", gd->getTileHeight()));
        gd->setTileWidth(node->getInteger("width", gd->getTileWidth()));
    }

    // Drawer
    if (key == "style")
    {
        auto rootNamespace = node->getString("namespace");

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
    auto gd = graphicData(shared);

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
        shared->getLog()->debug(getName(), "Beginning to render everything.");

        drawer.updateScreen(shared, gd->getZLevel());
        drawer.renderNow(shared);
        gd->setRenderEverything(false);

        shared->getLog()->debug(getName(), "Finished rendering.");
    }
    else
    {
        auto changedPos = getDataValue<RegionManager>(shared, ModelIds::regionManager())->getChangedPos();
        if (!changedPos.empty())
        {
            auto msg = boost::format("Beginning to render %1% positions.") % changedPos.size();
            shared->getLog()->debug(getName(), msg.str());

            drawer.updatePositions(shared, changedPos, gd->getZLevel());
            drawer.renderNow(shared);

            shared->getLog()->debug(getName(), "Finished rendering.");
        }
    }
}

void frts::Sdl2Renderer::validateData(SharedManagerPtr shared)
{
    // Graphic Data
    auto gd = graphicData(shared);

    if (gd->getMaxFps() == 0)
    {
        throw DataViolation("Maximal frames per second must be greater than zero.");
    }

    if (gd->getNumFpsAvg() == 0)
    {
        throw DataViolation("Number of frames per second measures for average calculation must be greater than zero.");
    }

    if (gd->getScreenHeight() == 0)
    {
        throw DataViolation("Screen height must be greater than zero.");
    }

    if (gd->getScreenWidth() == 0)
    {
        throw DataViolation("Screen width must be greater than zero.");
    }

    if (gd->getScreenOffsetStepX() == 0)
    {
        throw DataViolation("Screen move width in x-direction must be greater than zero.");
    }

    if (gd->getScreenOffsetStepY() == 0)
    {
        throw DataViolation("Screen move width in y-direction must be greater than zero.");
    }

    if (gd->getTileHeight() == 0)
    {
        throw DataViolation("Tile height must be greater than zero.");
    }

    if (gd->getTileWidth() == 0)
    {
        throw DataViolation("Tile width must be greater than zero.");
    }

    // Drawer
    drawer.validateData(shared);
}

void frts::Sdl2Renderer::validateModules(SharedManagerPtr shared)
{
    // VanillaCommand.
    try
    {
        auto id = shared->makeId(CommandIds::commandFactory());
        shared->getUtility(id);
    }
    catch(const IdNotFoundError&)
    {
        throw ModuleViolation("Utility CommandFactory not found.");
    }

    // VanillaModel.
    try
    {
        auto id = shared->makeId(ModelIds::modelFactory());
        shared->getUtility(id);
    }
    catch(const IdNotFoundError&)
    {
        throw ModuleViolation("Utility ModelFactory not found.");
    }
}
