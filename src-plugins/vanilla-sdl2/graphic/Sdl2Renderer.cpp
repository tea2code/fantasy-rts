#include "Sdl2Renderer.h"

#include "impl/GraphicDataImpl.h"
#include "impl/RenderableBuilder.h"
#include <main/Sdl2Ids.h>

#include <boost/format.hpp>


bool frts::Sdl2Renderer::createData(SharedManagerPtr shared)
{
    auto gd = makeGraphicData();
    auto id = shared->makeId(Sdl2Ids::graphicData());
    shared->setDataValue(id, gd);

    return false;
}

frts::GraphicDataPtr frts::Sdl2Renderer::graphicData(SharedManagerPtr shared) const
{
    auto id = shared->makeId(Sdl2Ids::graphicData());
    return std::static_pointer_cast<GraphicData>(shared->getDataValue(id));
}

std::string frts::Sdl2Renderer::getName() const
{
    return "frts::SDL2Renderer";
}

std::vector<std::string> frts::Sdl2Renderer::getSupportedConfig()
{
    return {"style", "screen", "tile"};
}

int frts::Sdl2Renderer::getVersion() const
{
    return 1;
}

bool frts::Sdl2Renderer::init(SharedManagerPtr shared)
{
    // Register renderable.
    auto id = shared->makeId(ModelIds::modelFactory());
    auto modelFactory = std::static_pointer_cast<ModelFactory>(shared->getUtility(id));
    auto componentId = shared->makeId(Sdl2Ids::renderable());
    auto componentBuilder = makeRenderableBuilder();
    modelFactory->registerComponentBuilder(componentId, componentBuilder);

    // Init drawer
    drawer.init(shared);
    graphicData(shared)->setRenderEverything();

    return false;
}

void frts::Sdl2Renderer::parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared)
{
    // Graphic Data
    auto gd = graphicData(shared);
    if (key == "screen")
    {
        gd->setMaxFps(node->getInteger("fps", gd->getMaxFps()));
        gd->setScreenHeight(node->getInteger("height", gd->getScreenHeight()));
        gd->setScreenTitle(node->getString("title", gd->getScreenTitle()));
        gd->setScreenWidth(node->getInteger("width", gd->getScreenWidth()));
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

bool frts::Sdl2Renderer::preInit(SharedManagerPtr)
{
    return false;
}

void frts::Sdl2Renderer::tick(SharedManagerPtr shared)
{
    auto gd = graphicData(shared);

    // FpsManager
    fpsManager.limitFps(gd->getMaxFps());
    auto fps = fpsManager.calcFps();
    auto windowsTitle = boost::format(gd->getScreenTitle()) % fps;

    // Drawer
    drawer.setWindowTitle(windowsTitle.str());
    if (gd->isRenderEverything())
    {
        drawer.updateScreen(shared, gd->getZLevel());
        gd->setRenderEverything(false);
    }
    else
    {
        auto id = shared->makeId(ModelIds::regionManager());
        auto rm = std::static_pointer_cast<RegionManager>(shared->getDataValue(id));
        drawer.updatePositions(shared, rm->getChangedPos(), gd->getZLevel());
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

    if (gd->getScreenHeight() == 0)
    {
        throw DataViolation("Screen height must be greater than zero.");
    }

    if (gd->getScreenWidth() == 0)
    {
        throw DataViolation("Screen width must be greater than zero.");
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
        IdPtr id = shared->makeId("frts/CommandFactory");
        shared->getUtility(id);
    }
    catch(const IdNotFoundError&)
    {
        throw ModuleViolation("Utility CommandFactory not found.");
    }

    // VanillaModel.
    try
    {
        IdPtr id = shared->makeId("frts/ModelFactory");
        shared->getUtility(id);
    }
    catch(const IdNotFoundError&)
    {
        throw ModuleViolation("Utility ModelFactory not found.");
    }
}
