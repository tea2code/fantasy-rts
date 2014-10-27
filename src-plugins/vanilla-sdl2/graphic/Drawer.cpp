#include "Drawer.h"


frts::Drawer::Drawer(SharedManagerPtr shared)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        shared->getLog()->error(getName(), "SDL_Init Error: " + std::string(SDL_GetError()));
        return;
    }

    int imageFlags = IMG_INIT_PNG;
    if (IMG_Init(imageFlags) != imageFlags)
    {
        shared->getLog()->error(getName(), "IMG_Init Error: " + std::string(IMG_GetError()));
        return;
    }

    window = std::unique_ptr<SDL_Window>(
       SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        (tileWidth * screenWidth), (tileHeight * screenHeight), SDL_WINDOW_SHOWN)
    );
    if (window == nullptr)
    {
        shared->getLog()->error(getName(), "SDL_CreateWindow Error: " + std::string(SDL_GetError()));
        return;
    }

    renderer = std::unique_ptr<SDL_Renderer>(
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
    );
    if (renderer == nullptr)
    {
        shared->getLog()->error(getName(), "SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
        return;
    }

    initialized = true;
}

frts::Drawer::~Drawer()
{
    SDL_DestroyTexture(texture.get());
    SDL_DestroyRenderer(renderer.get());
    SDL_DestroyWindow(window.get());
    IMG_Quit();
    SDL_Quit();
}

frts::ModelFactoryPtr frts::Drawer::modelFactory(SharedManagerPtr shared) const
{
    return nullptr; // TODO
}

frts::RegionManagerPtr frts::Drawer::regionManager(SharedManagerPtr shared) const
{
    return nullptr; // TODO
}

void frts::Drawer::setOffsetX(Point::value offsetX)
{
    this->offsetX = offsetX;
}

void frts::Drawer::setOffsetY(Point::value offsetY)
{
    this->offsetY = offsetY;
}


void frts::Drawer::updatePosition(SharedManagerPtr shared, PointPtr pos, Point::value)
{
    if (!initialized)
    {
        return;
    }


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
    for (Point::value x = offsetX; x < (offsetX + screenWidth); ++x)
    {
        for (Point::value y = offsetY; y < (offsetY + screenHeight); ++y)
        {
            PointPtr pos = nullptr; // TOOD
            updatePosition(shared, pos, zLevel);
        }
    }
}
