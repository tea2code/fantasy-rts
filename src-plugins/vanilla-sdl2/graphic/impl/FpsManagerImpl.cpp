#include "FpsManagerImpl.h"

#include <SDL2/SDL.h>


frts::FpsManagerImpl::FpsManagerImpl()
    : lastFps{0}, lastTime{SDL_GetTicks()}
{
}

double frts::FpsManagerImpl::calcFps()
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

void frts::FpsManagerImpl::limitFps(double)
{
    // TODO Currently do nothing.
}
