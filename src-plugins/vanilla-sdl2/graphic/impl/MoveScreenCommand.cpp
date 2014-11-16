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
    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto rc = getDataValue<RegionConfig>(shared, ModelIds::regionConfig());

    Point::value undoX = -x;
    Point::value undoY = -y;
    Point::value undoZ = -z;

    if (lastX)
    {
        // X -> West
        if (undoX > 0 && gd->getScreenOffsetX() > 0)
        {
            auto offset = std::max(gd->getScreenOffsetX() - undoX, 0);
            gd->setScreenOffsetX(offset);
            gd->setRenderEverything(true);
        }

        // X -> East
        Point::value maxX = rc->getMapSizeX() - (gd->getScreenWidth() / gd->getTileWidth());
        if (undoX < 0 && gd->getScreenOffsetX() < maxX)
        {
            auto offset = std::min(gd->getScreenOffsetX() - undoX, maxX);
            gd->setScreenOffsetX(offset);
            gd->setRenderEverything(true);
        }
    }

    if (lastY)
    {
        // Y -> North
        if (undoY > 0 && gd->getScreenOffsetY() > 0)
        {
            auto offset = std::max(gd->getScreenOffsetY() - undoY, 0);
            gd->setScreenOffsetY(offset);
            gd->setRenderEverything(true);
        }

        // Y -> South
        Point::value maxY = rc->getMapSizeY() - (gd->getScreenHeight() / gd->getTileHeight());
        if (undoY < 0 && gd->getScreenOffsetY() < maxY)
        {
            auto offset = std::min(gd->getScreenOffsetY() - undoY, maxY);
            gd->setScreenOffsetY(offset);
            gd->setRenderEverything(true);
        }
    }

    if (lastZ)
    {
        // Z -> Up/Down
        if (undoZ != 0)
        {
            gd->setZLevel(gd->getZLevel() + undoZ);
            gd->setRenderEverything(true);
        }
    }

    lastX = lastY = lastZ = false;
}
