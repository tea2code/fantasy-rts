#include "GraphicUtility.h"


frts::Point::value frts::screenToRegion(unsigned int screen, int tile)
{
    return screen / tile;
}


unsigned int frts::regionToScreen(Point::value region, int tile)
{
    return region * tile;
}
