#include "FpsManager.h"

#include <SDL2/SDL.h>

#include <numeric>


frts::FpsManager::FpsManager()
    : lastLimitTime{SDL_GetTicks()}, lastTime{SDL_GetTicks()}
{
    setNumFpsAvg();
}

unsigned int frts::FpsManager::calcFps()
{
    unsigned int currentTime = SDL_GetTicks();
    unsigned int diff = currentTime - lastTime;
    if (diff > 0)
    {
        unsigned int newFps = 1000 / diff;
        fpsTotal += newFps;
        fpsQueue.push_back(newFps);
        lastTime = currentTime;   
    }
    while (fpsQueue.size() > numFpsAvg)
    {
        fpsTotal -= fpsQueue.front();
        fpsQueue.pop_front();
    }
    if (fpsQueue.empty())
    {
        // Default fps if no value is inserted.
        return 9999;
    }
//    return std::accumulate(fpsQueue.begin(), fpsQueue.end(), 0) / fpsQueue.size();
    return fpsTotal / fpsQueue.size();
}

void frts::FpsManager::limitFps(unsigned int fps)
{
    unsigned int msPerFrame = 1000 / fps;
    unsigned int diff = SDL_GetTicks() - lastLimitTime;
    if (diff < msPerFrame)
    {
        SDL_Delay(msPerFrame - diff);
    }
    lastLimitTime = SDL_GetTicks();
}

void frts::FpsManager::setNumFpsAvg(unsigned int numFpsAvg)
{
    this->numFpsAvg = numFpsAvg;
}
