#include "VanillaSdl2Tickable.h"

#include <frts/shared>

#include <boost/format.hpp>
#include <SDL2/SDL_image.h>

#include <string>


frts::VanillaSdl2Tickable::VanillaSdl2Tickable()
{
}

frts::VanillaSdl2Tickable::~VanillaSdl2Tickable()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
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

    int imageFlags = IMG_INIT_PNG;
    if (IMG_Init(imageFlags) != imageFlags)
    {
        shared->getLog()->error(getName(), "IMG_Init Error: " + std::string(IMG_GetError()));
        return false;
    }

    window = SDL_CreateWindow("Hello World!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 640, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        shared->getLog()->error(getName(), "SDL_CreateWindow Error: " + std::string(SDL_GetError()));
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        shared->getLog()->error(getName(), "SDL_CreateRenderer Error: " + std::string(SDL_GetError()));
        return false;
    }

    SDL_Surface *surface = IMG_Load("plugins/vanilla-sdl2/sprite.png");
    if (surface == nullptr)
    {
        shared->getLog()->error(getName(), "IMG_Load Error: " + std::string(IMG_GetError()));
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr)
    {
        shared->getLog()->error(getName(), "SDL_CreateTextureFromSurface Error: " + std::string(SDL_GetError()));
        return false;
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    lastTime = SDL_GetTicks();

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
    unsigned int currentTime = SDL_GetTicks();
    unsigned int diff = currentTime - lastTime;
    if (diff > 0)
    {
        unsigned int fps = 1000 / diff;
        lastTime = currentTime;
        auto msg = boost::format(R"(Fps = %1%)") % fps;
        SDL_SetWindowTitle(window, msg.str().c_str());
    }
}

void frts::VanillaSdl2Tickable::validateData(frts::SharedManagerPtr)
{
    // Everything is ok.
}

void frts::VanillaSdl2Tickable::validateModules(frts::SharedManagerPtr shared)
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
