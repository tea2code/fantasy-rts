#include "FpsManager.h"

#include <SDL2/SDL.h>


frts::FpsManager::FpsManager()
    : lastFps{0}, lastTime{SDL_GetTicks()}
{
}

unsigned int frts::FpsManager::calcFps()
{
    unsigned int currentTime = SDL_GetTicks();
    unsigned int diff = currentTime - lastTime;
    if (diff > 0)
    {
        unsigned int fps = 1000 / diff;
        lastFps = fps;
        lastTime = currentTime;

        return fps;
    }
    else
    {
        return lastFps;
    }
}

void frts::FpsManager::limitFps(unsigned int)
{
    // TODO Currently do nothing.
}
