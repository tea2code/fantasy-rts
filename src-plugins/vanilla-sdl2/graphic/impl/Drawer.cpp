#include "Drawer.h"

#include "GraphicUtility.h"
#include <main/Sdl2Ids.h>

#include <frts/file.h>
#include <frts/vanillamodel>

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
    renderer.release();
    window.release();
    IMG_Quit();
    SDL_Quit();
}

std::string frts::Drawer::getName() const
{
    return "frts::SDL2Drawer";
}

void frts::Drawer::init(SharedManagerPtr shared)
{
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

    // Initialize SDL2.
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        shared->getLog()->error("SDL2 Drawer", "SDL_Init Error: " + std::string(SDL_GetError()));
        return;
    }

    int imageFlags = IMG_INIT_PNG;
    if (IMG_Init(imageFlags) != imageFlags)
    {
        shared->getLog()->error("SDL2 Drawer", "IMG_Init Error: " + std::string(IMG_GetError()));
        return;
    }

    window = std::unique_ptr<SDL_Window, Sdl2Deleter>(
       SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        regionToScreen(screenWidth, tileWidth), regionToScreen(screenHeight, tileHeight),
                        SDL_WINDOW_SHOWN),
        Sdl2Deleter()
    );
    if (window == nullptr)
    {
        shared->getLog()->error(getName(), "SDL_CreateWindow Error: " + std::string(SDL_GetError()));
        return;
    }

    renderer = std::unique_ptr<SDL_Renderer, Sdl2Deleter>(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED),
        Sdl2Deleter()
    );
    if (renderer == nullptr)
    {
        shared->getLog()->error(getName(), "SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
        return;
    }

    for (auto& image : images)
    {
        SDL_Surface *surface = IMG_Load(image.second.c_str());
        if (surface == nullptr)
        {
            shared->getLog()->error(getName(), "IMG_Load Error: " + std::string(IMG_GetError()));
            continue;
        }

        TexturePtr texture = std::shared_ptr<SDL_Texture>(
            SDL_CreateTextureFromSurface(renderer.get(), surface),
            Sdl2Deleter()
        );
        SDL_FreeSurface(surface);
        if (texture == nullptr)
        {
            shared->getLog()->error(getName(), "SDL_CreateTextureFromSurface Error: " + std::string(SDL_GetError()));
            continue;
        }

        textures.insert(std::make_pair(image.first, texture));
    }
    images.clear();

    initialized = true;
}

void frts::Drawer::renderNow(SharedManagerPtr shared)
{
    if (!initialized)
    {
        shared->getLog()->warning(getName(), "Tried to call renderNow() without init().");
        return;
    }

    SDL_RenderPresent(renderer.get());
}

void frts::Drawer::setImageConfig(SharedManagerPtr shared, const std::string& rootNamespace, ConfigNodePtr imagesNode)
{
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
    spriteManager.setConfig(shared, rootNamespace, spritesNode);
}

void frts::Drawer::setWindowTitle(const std::string& windowTitle)
{
    SDL_SetWindowTitle(window.get(), windowTitle.c_str());
}

void frts::Drawer::updatePosition(SharedManagerPtr shared, PointPtr pos, Point::value zLevel)
{
    if (!initialized)
    {
        shared->getLog()->warning(getName(), "Tried to call updatePosition() without init().");
        return;
    }

    // Currently we only render on the same z-level.
    // Idea for future implementation: Render lower levels
    // with an partial transparent overlay to indicate depth.
    if (pos->getZ() != zLevel)
    {
        return;
    }

    auto block = getDataValue<RegionManager>(shared, ModelIds::regionManager())->getBlock(pos, shared);
    auto renderableId = shared->makeId(Sdl2Ids::renderable());
    auto entities = block->getByComponent(renderableId);

    for (auto& entity : entities)
    {
        auto renderable = getComponent<Renderable>(renderableId, entity);
        auto sprite = spriteManager.getSprite(renderable);
        auto texture = textures.at(sprite.getImage());

        SDL_Rect clip = {
            sprite.getX(),
            sprite.getY(),
            sprite.getWidth(),
            sprite.getHeight()
        };
        SDL_Rect rectToRender = {
            static_cast<int>(regionToScreen(pos->getX() - offsetX, tileWidth)),
            static_cast<int>(regionToScreen(pos->getY() - offsetY, tileHeight)),
            tileWidth,
            tileHeight
        };
        SDL_RenderCopy(renderer.get(), texture.get(), &clip, &rectToRender);
    }
}

void frts::Drawer::updatePositions(SharedManagerPtr shared, const RegionManager::PointSet& positions, Point::value zLevel)
{
    for (PointPtr pos : positions)
    {
        updatePosition(shared, pos, zLevel);
    }
}

void frts::Drawer::updateScreen(SharedManagerPtr shared, Point::value zLevel)
{
    auto factory = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    Point::value width = offsetX + screenWidth;
    Point::value height = offsetY + screenHeight;

    for (Point::value x = offsetX; x < width; ++x)
    {
        for (Point::value y = offsetY; y < height; ++y)
        {
            auto pos = factory->makePoint(x, y, zLevel);
            updatePosition(shared, pos, zLevel);
        }
    }
}

void frts::Drawer::validateData(SharedManagerPtr shared)
{
    spriteManager.validateData(shared);

    for (auto& image : images)
    {
        if (!fileExists(image.second))
        {
            auto msg = boost::format(R"(Image "%1%" with path "%2%" not found.)") % image.first->toString() % image.second;
            throw InvalidImageConfigError(msg.str());
        }
    }
}
