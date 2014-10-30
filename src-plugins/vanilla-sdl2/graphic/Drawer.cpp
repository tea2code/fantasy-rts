#include "Drawer.h"

#include <SDL2/SDL_image.h>


frts::Drawer::Drawer()
{}

frts::Drawer::~Drawer()
{
    for (auto& it : textures)
    {
        it.second.release();
    }
    renderer.release();
    window.release();
    IMG_Quit();
    SDL_Quit();
}

void frts::Drawer::init(SharedManagerPtr shared)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        shared->getLog()->error("SDL2 Drawer", "SDL_Init Error: " + std::string(SDL_GetError()));
        return;
    }

    int imageFlags = IMG_INIT_PNG; // TODO
    if (IMG_Init(imageFlags) != imageFlags)
    {
        shared->getLog()->error("SDL2 Drawer", "IMG_Init Error: " + std::string(IMG_GetError()));
        return;
    }

    window = std::unique_ptr<SDL_Window, Sdl2Deleter>(
       SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        (tileWidth * screenWidth), (tileHeight * screenHeight), SDL_WINDOW_SHOWN),
        Sdl2Deleter()
    );
    if (window == nullptr)
    {
        shared->getLog()->error("SDL2 Drawer", "SDL_CreateWindow Error: " + std::string(SDL_GetError()));
        return;
    }

    renderer = std::unique_ptr<SDL_Renderer, Sdl2Deleter>(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
        Sdl2Deleter()
    );
    if (renderer == nullptr)
    {
        shared->getLog()->error("SDL2 Drawer", "SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
        return;
    }

    // TODO Textures

    initialized = true;
}

frts::ModelFactoryPtr frts::Drawer::modelFactory(SharedManagerPtr shared) const
{
    IdPtr id = shared->makeId(ModelIds::modelFactory());
    return std::static_pointer_cast<ModelFactory>(shared->getUtility(id));
}

frts::RegionManagerPtr frts::Drawer::regionManager(SharedManagerPtr shared) const
{
    IdPtr id = shared->makeId(ModelIds::regionManager());
    return std::static_pointer_cast<RegionManager>(shared->getDataValue(id));
}

void frts::Drawer::setImageConfig(SharedManagerPtr shared, const std::string& rootNamespace, ConfigNodePtr imagesNode)
{
    // TODO
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

void frts::Drawer::updatePosition(SharedManagerPtr shared, PointPtr pos, Point::value)
{
    if (!initialized)
    {
        return;
    }

    // TODO
}

void frts::Drawer::updatePositions(SharedManagerPtr shared, std::vector<PointPtr> positions, Point::value zLevel)
{
    for (PointPtr pos : positions)
    {
        updatePosition(shared, pos, zLevel);
    }
}

void frts::Drawer::updateScreen(SharedManagerPtr shared, Point::value zLevel)
{
    auto factory = modelFactory(shared);

    for (Point::value x = offsetX; x < (offsetX + screenWidth); ++x)
    {
        for (Point::value y = offsetY; y < (offsetY + screenHeight); ++y)
        {
            PointPtr pos = factory->makePoint(x, y, zLevel);
            updatePosition(shared, pos, zLevel);
        }
    }
}

void frts::Drawer::validateData(SharedManagerPtr shared)
{
    spriteManager.validateData(shared);
    // TODO
}
