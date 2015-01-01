#include "GraphicUtility.h"


frts::Point::value frts::screenToRegion(GraphicData::pixel screen, int tile)
{
    return screen / tile;
}


frts::GraphicData::pixel frts::regionToScreen(Point::value region, int tile)
{
    return region * tile;
}
