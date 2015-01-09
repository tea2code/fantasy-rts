#include "Drawer.h"

#include "GraphicUtility.h"
#include <main/Sdl2Ids.h>

#include <frts/file.h>
#include <frts/vanillamodel>
#include <frts/timer.h>

#include <boost/format.hpp>
#include <SDL2/SDL_image.h>

#include <algorithm>
#include <utility>


frts::Drawer::Drawer()
{}

frts::Drawer::~Drawer()
{
    for (auto& it : textures)
    {
        it.second.reset();
    }
    renderer.reset();
    window.release();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

std::string frts::Drawer::getName() const
{
    return "frts::SDL2Drawer";
}

frts::Drawer::RendererPtr frts::Drawer::getRenderer() const
{
    assert(initialized);

    return renderer;
}

void frts::Drawer::init(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    // Set data from config.
    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto md = getDataValue<ModelData>(shared, ModelIds::modelData());

    tileHeight = gd->getTileHeight();
    tileWidth = gd->getTileWidth();

    screenHeight = screenToRegion(gd->getScreenHeight(), tileHeight);
    screenHeight = std::min(screenHeight, md->getMapSizeY());
    gd->setScreenHeight(regionToScreen(screenHeight, tileHeight));

    screenWidth = screenToRegion(gd->getScreenWidth(), tileWidth);
    screenWidth = std::min(screenWidth, md->getMapSizeX());
    gd->setScreenWidth(regionToScreen(screenWidth, tileWidth));

    sidebarWidth = screenToRegion(gd->getSidebarWidth(), tileWidth);
    gd->setSidebarWidth(regionToScreen(sidebarWidth, tileWidth));

    mapWidth = screenWidth - sidebarWidth;

    // Set screen areas.
    GraphicData::ScreenArea mapArea(0, 0, regionToScreen(mapWidth, tileWidth), gd->getScreenHeight());
    gd->setMapArea(mapArea);

    GraphicData::ScreenArea sidebarArea(regionToScreen(mapWidth, tileWidth), 0, gd->getSidebarWidth(), gd->getScreenHeight());
    gd->setSidebarArea(sidebarArea);

    // Initialize SDL2.
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        auto msg = boost::format(R"(SDL_Init Error: %1%)") % SDL_GetError();
        shared->getLog()->error(getName(), msg.str());
        return;
    }

    // Image support.
    int imageFlags = IMG_INIT_PNG;
    if (IMG_Init(imageFlags) != imageFlags)
    {
        auto msg = boost::format(R"(IMG_Init Error: %1%)") % IMG_GetError();
        shared->getLog()->error(getName(), msg.str());
        return;
    }

    // TTF support.
    if(TTF_Init() == -1)
    {
        auto msg = boost::format(R"(TTF_Init Error: %1%)") % TTF_GetError();
        shared->getLog()->error(getName(), msg.str());
        return;
    }

    // Create window.
    window = std::unique_ptr<SDL_Window, Sdl2Deleter>(
       SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        regionToScreen(screenWidth, tileWidth), regionToScreen(screenHeight, tileHeight),
                        SDL_WINDOW_SHOWN),
        Sdl2Deleter()
    );
    if (window == nullptr)
    {
        auto msg = boost::format(R"(SDL_CreateWindow Error: %1%)") % SDL_GetError();
        shared->getLog()->error(getName(), msg.str());
        return;
    }

    // Create renderer.
    renderer = std::shared_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED),
        Sdl2Deleter()
    );
    if (renderer == nullptr)
    {
        auto msg = boost::format(R"(SDL_CreateRenderer Error: %1%)") % SDL_GetError();
        shared->getLog()->error(getName(), msg.str());
        return;
    }

    // Read images.
    for (auto& image : images)
    {
        SDL_Surface *surface = IMG_Load(image.second.c_str());
        if (surface == nullptr)
        {
            auto msg = boost::format(R"(IMG_Load Error: %1%)") % IMG_GetError();
            shared->getLog()->error(getName(), msg.str());
            continue;
        }

        TexturePtr texture = std::shared_ptr<SDL_Texture>(
            SDL_CreateTextureFromSurface(renderer.get(), surface),
            Sdl2Deleter()
        );
        SDL_FreeSurface(surface);
        if (texture == nullptr)
        {
            auto msg = boost::format(R"(SDL_CreateTextureFromSurface Error: %1%)") % SDL_GetError();
            shared->getLog()->error(getName(), msg.str());
            continue;
        }

        textures.insert(std::make_pair(image.first, texture));
    }
    images.clear();

    initialized = true;
}

void frts::Drawer::renderEntities(const std::vector<EntityPtr>& entities, IdPtr renderableId,
                                  const SDL_Rect& rectToRender, SharedManagerPtr shared)
{
    assert(initialized);
    assert(renderableId != nullptr);
    assert(shared != nullptr);

    for (auto& entity : entities)
    {
        auto renderable = getComponent<Renderable>(renderableId, entity);
        auto sprite = spriteManager.getSprite(renderable, entity, shared);
        auto texture = textures.at(sprite.getImage());

        SDL_Rect clip = {
            sprite.getX(),
            sprite.getY(),
            sprite.getWidth(),
            sprite.getHeight()
        };
        SDL_RenderCopy(renderer.get(), texture.get(), &clip, &rectToRender);
    }
}

void frts::Drawer::renderNow(SharedManagerPtr shared)
{
    assert(shared != nullptr);
    assert(initialized);

    PerformanceLog pl(getName() + "RenderNow", shared, 5);

    SDL_RenderPresent(renderer.get());
}

void frts::Drawer::setTileBackground(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
    tileBackgroundR = r;
    tileBackgroundG = g;
    tileBackgroundB = b;
}

void frts::Drawer::setImageConfig(SharedManagerPtr shared, const std::string& rootNamespace, ConfigNodePtr imagesNode)
{
    assert(shared != nullptr);
    assert(imagesNode != nullptr);

    // Namepspace.
    std::string ns = rootNamespace;
    if (imagesNode->has("namespace"))
    {
        ns = ns + "." + imagesNode->getString("namespace");
    }

    // Plugin path.
    auto plugins = getDataValue<MainData>(shared, MainIds::mainData())->getPluginPath();

    // Images.
    auto node = imagesNode->getNode("image");
    for (auto imageNode : *node)
    {
        auto id = shared->makeId(ns + "." + imageNode->getString("name"));
        std::string path = plugins + imageNode->getString("path");
        images.insert(std::make_pair(id, path));
    }
}

void frts::Drawer::setOffsetX(Point::value offsetX)
{
    this->offsetX = offsetX;
}

void frts::Drawer::setOffsetY(Point::value offsetY)
{
    this->offsetY = offsetY;
}

void frts::Drawer::setSpriteConfig(SharedManagerPtr shared, const std::string& rootNamespace, ConfigNodePtr spritesNode)
{
    assert(shared != nullptr);
    assert(spritesNode != nullptr);

    spriteManager.setConfig(shared, rootNamespace, spritesNode);
}

void frts::Drawer::setWindowTitle(const std::string& windowTitle)
{
    SDL_SetWindowTitle(window.get(), windowTitle.c_str());
}

void frts::Drawer::updateMap(SharedManagerPtr shared, Point::value zLevel,
                                RegionManagerPtr regionManager, ModelFactoryPtr modelFactory, GraphicDataPtr graphicData)
{
    assert(shared != nullptr);

    PerformanceLog pl(getName() + " UpdateMap", shared);

    Point::value width = offsetX + mapWidth;
    Point::value height = offsetY + screenHeight;

    for (Point::value x = offsetX; x < width; ++x)
    {
        for (Point::value y = offsetY; y < height; ++y)
        {
            auto pos = modelFactory->makePoint(x, y, zLevel);
            updatePosition(shared, pos, zLevel, regionManager, modelFactory, graphicData);
        }
    }
}

void frts::Drawer::updatePosition(SharedManagerPtr shared, PointPtr pos, Point::value zLevel,
                                  RegionManagerPtr regionManager, ModelFactoryPtr modelFactory, GraphicDataPtr graphicData)
{
    assert(shared != nullptr);
    assert(pos != nullptr);
    assert(initialized);

    // We only render on the same z-level or levels below.
    if (pos->getZ() > zLevel)
    {
        return;
    }

    // Change pos if it is below because we render always relative to the current zLevel.
    // Also we check if it is necessary to render (this may change later depending on transparency).
    bool renderPos = (pos->getZ() == zLevel);
    if (pos->getZ() < zLevel)
    {
        pos = modelFactory->makePoint(pos->getX(), pos->getY(), zLevel);
    }

    // The rectangle on the screen which should be rendered.
    auto mapArea = graphicData->getMapArea();
    auto renderX = mapArea.x + regionToScreen(pos->getX() - offsetX, tileWidth);
    auto renderY = mapArea.y + regionToScreen(pos->getY() - offsetY, tileHeight);
    SDL_Rect rectToRender = {
        static_cast<int>(renderX),
        static_cast<int>(renderY),
        tileWidth,
        tileHeight
    };
    SDL_SetRenderDrawColor(renderer.get(), tileBackgroundR, tileBackgroundG, tileBackgroundB, 0);

    // Check if the position is in the map rectangle.
    if (!mapArea.isPixelInRect(renderX, renderY))
    {
        return;
    }

    // Get block.
    auto renderableId = shared->makeId(Sdl2Ids::renderable());
    auto block = regionManager->getBlock(pos, shared);
    auto entities = block->getByComponent(renderableId);

    // Check for transparency. Currently we only render blocks below if the first entity (the assumed background) has it.
    auto filledBackground = false;
    if (entities.size() > 0)
    {
        auto entity = entities.at(0);
        auto renderable = getComponent<Renderable>(renderableId, entity);
        auto transparency = renderable->getTransparency();

        if (transparency > 0)
        {
            SDL_RenderFillRect(renderer.get(), &rectToRender);
            filledBackground = true;
        }
        while (transparency > 0)
        {
            auto posBelow = modelFactory->makePoint(pos->getX(), pos->getY(), pos->getZ() - transparency);
            auto blockBelow = regionManager->getBlock(posBelow, shared);
            auto entitiesBelow = blockBelow->getByComponent(renderableId);
            renderEntities(entitiesBelow, renderableId, rectToRender, shared);
            transparency -= 1;
            renderPos = true;
        }
    }

    if (renderPos)
    {
        if (!filledBackground)
        {
            SDL_RenderFillRect(renderer.get(), &rectToRender);
        }

        renderEntities(entities, renderableId, rectToRender, shared);
    }
}

void frts::Drawer::updatePositions(SharedManagerPtr shared, const PointUnorderedSet& positions, Point::value zLevel,
                                   RegionManagerPtr regionManager, ModelFactoryPtr modelFactory, GraphicDataPtr graphicData)
{
    assert(shared != nullptr);

    PerformanceLog pl(getName() + " UpdatePositions", shared, 2);

    for (PointPtr pos : positions)
    {
        updatePosition(shared, pos, zLevel, regionManager, modelFactory, graphicData);
    }
}

void frts::Drawer::validateData(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    spriteManager.validateData(shared);

    for (auto& image : images)
    {
        if (!fileExists(image.second))
        {
            auto msg = boost::format(R"(Drawer: Image "%1%" with path "%2%" not found.)") % image.first->toString() % image.second;
            throw InvalidImageConfigError(msg.str());
        }
    }
}
