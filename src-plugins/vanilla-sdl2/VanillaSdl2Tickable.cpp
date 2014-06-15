#include "VanillaSdl2Tickable.h"

#include <frts/shared>

#include <string>


frts::VanillaSdl2Tickable::VanillaSdl2Tickable()
{
}

frts::VanillaSdl2Tickable::~VanillaSdl2Tickable()
{
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

bool frts::VanillaSdl2Tickable::createData(frts::SharedManagerPtr)
{
    return false;
}

std::string frts::VanillaSdl2Tickable::getName() const
{
    return "frts::VanillaSdl2Tickable";
}

std::vector<std::string> frts::VanillaSdl2Tickable::getSupportedConfig()
{
    return {};
}

int frts::VanillaSdl2Tickable::getVersion() const
{
    return 1;
}

bool frts::VanillaSdl2Tickable::init(frts::SharedManagerPtr shared)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        shared->getLog()->error(getName(), "SDL_Init Error: " + std::string(SDL_GetError()));
        return false;
    }

    win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr)
    {
        shared->getLog()->error(getName(), "SDL_CreateWindow Error: " + std::string(SDL_GetError()));
        return false;
    }

    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr)
    {
        shared->getLog()->error(getName(), "SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
        return false;
    }

    SDL_Surface *bmp = SDL_LoadBMP("F:/Programmieren/scripts/SDL2/hello.bmp");
    if (bmp == nullptr)
    {
        shared->getLog()->error(getName(), "SDL_LoadBMP Error: " + std::string(SDL_GetError()));
        return false;
    }

    tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == nullptr)
    {
        shared->getLog()->error(getName(), "SDL_CreateTextureFromSurface Error: " + std::string(SDL_GetError()));
        return false;
    }

    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);

    return false;
}

void frts::VanillaSdl2Tickable::parseConfig(const std::string&, frts::ConfigNodePtr, frts::SharedManagerPtr)
{

}

bool frts::VanillaSdl2Tickable::preInit(frts::SharedManagerPtr)
{
    return false;
}

void frts::VanillaSdl2Tickable::tick(frts::SharedManagerPtr)
{

}

void frts::VanillaSdl2Tickable::validateData(frts::SharedManagerPtr)
{
    // Everything is ok.
}

void frts::VanillaSdl2Tickable::validateModules(frts::SharedManagerPtr)
{

}
