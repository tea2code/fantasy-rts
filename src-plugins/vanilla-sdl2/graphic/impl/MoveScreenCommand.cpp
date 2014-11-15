#include "MoveScreenCommand.h"

#include <graphic/GraphicData.h>
#include <main/Sdl2Ids.h>

#include <algorithm>


frts::MoveScreenCommand::MoveScreenCommand(Point::value x, Point::value y, Point::value z)
    : x{x}, y{y}, z{z}
{}

void frts::MoveScreenCommand::execute(SharedManagerPtr shared)
{
    lastX = lastY = lastZ = false;

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto rc = getDataValue<RegionConfig>(shared, ModelIds::regionConfig());

    // X -> West
    if (x > 0 && gd->getScreenOffsetX() > 0)
    {
        auto offset = std::max(gd->getScreenOffsetX() - x, 0);
        gd->setScreenOffsetX(offset);
        lastX = true;
    }

    // X -> East
    Point::value maxX = rc->getMapSizeX() - (gd->getScreenWidth() / gd->getTileWidth());
    if (x < 0 && gd->getScreenOffsetX() < maxX)
    {
        auto offset = std::min(gd->getScreenOffsetX() - x, maxX);
        gd->setScreenOffsetX(offset);
        lastX = true;
    }

    // Y -> North
    if (y > 0 && gd->getScreenOffsetY() > 0)
    {
        auto offset = std::max(gd->getScreenOffsetY() - y, 0);
        gd->setScreenOffsetY(offset);
        lastY = true;
    }

    // Y -> South
    Point::value maxY = rc->getMapSizeY() - (gd->getScreenHeight() / gd->getTileHeight());
    if (y < 0 && gd->getScreenOffsetY() < maxY)
    {
        auto offset = std::min(gd->getScreenOffsetY() - y, maxY);
        gd->setScreenOffsetY(offset);
        lastY = true;
    }

    // Z -> Up/Down
    if (z != 0)
    {
        gd->setZLevel(gd->getZLevel() + z);
        lastZ = true;
    }

    if (lastX || lastY || lastZ)
    {
        gd->setRenderEverything(true);
    }
}

void frts::MoveScreenCommand::undo(SharedManagerPtr shared)
{

}
