#include "GraphicUtility.h"


frts::Point::value frts::screenToRegion(GraphicData::Pixel screen, int tile)
{
    return screen / tile;
}


frts::GraphicData::Pixel frts::regionToScreen(Point::value region, int tile)
{
    return region * tile;
}
