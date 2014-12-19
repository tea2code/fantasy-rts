#include "MoveCursorCommand.h"

#include <graphic/GraphicData.h>
#include "GraphicUtility.h"
#include <main/Sdl2Ids.h>

#include <algorithm>


frts::MoveCursorCommand::MoveCursorCommand(IdPtr commandType, Point::value x, Point::value y, Point::value z)
    : commandType{commandType}, x{x}, y{y}, z{z}
{
}

void frts::MoveCursorCommand::execute(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    lastX = lastY = lastZ = false;

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    // Old cursor position.
    auto cursorPos = rm->getPos(gd->getCursor(), shared);
    rm->addChangedPos(cursorPos);

    // X -> West
    if (x > 0 && cursorPos->getX() > gd->getScreenOffsetX())
    {
        auto newX = std::max(cursorPos->getX() - x, 0);
        cursorPos = mf->makePoint(newX, cursorPos->getY(), cursorPos->getZ());
        lastX = true;
    }

    // X -> East
    Point::value maxX = gd->getScreenOffsetX() + screenToRegion(gd->getScreenWidth(), gd->getTileWidth());
    if (x < 0 && cursorPos->getX() < maxX)
    {
        auto newX = std::min(cursorPos->getX() - x, maxX - 1);
        cursorPos = mf->makePoint(newX, cursorPos->getY(), cursorPos->getZ());
        lastX = true;
    }

    // Y -> North
    if (y > 0 && cursorPos->getY() > gd->getScreenOffsetY())
    {
        auto newY = std::max(cursorPos->getY() - y, 0);
        cursorPos = mf->makePoint(cursorPos->getX(), newY, cursorPos->getZ());
        lastY = true;
    }

    // Y -> South
    Point::value maxY = gd->getScreenOffsetY() + screenToRegion(gd->getScreenHeight(), gd->getTileHeight());
    if (y < 0 && cursorPos->getY() < maxY)
    {
        auto newY = std::min(cursorPos->getY() - y, maxY - 1);
        cursorPos = mf->makePoint(cursorPos->getX(), newY, cursorPos->getZ());
        lastY = true;
    }

    // Z -> Up/Down
    if (z != 0)
    {
        cursorPos = mf->makePoint(cursorPos->getX(), cursorPos->getY(), cursorPos->getZ() + z);
        lastZ = true;
    }

    rm->setPos(gd->getCursor(), cursorPos, shared);
}

frts::IdPtr frts::MoveCursorCommand::getCommandType() const
{
    return commandType;
}

void frts::MoveCursorCommand::undo(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    // Old cursor position.
    auto cursorPos = rm->getPos(gd->getCursor(), shared);
    rm->addChangedPos(cursorPos);

    Point::value undoX = -x;
    Point::value undoY = -y;
    Point::value undoZ = -z;

    if (lastX)
    {
        // X -> West
        if (undoX > 0 && cursorPos->getX() > gd->getScreenOffsetX())
        {
            auto newX = std::max(cursorPos->getX() - undoX, 0);
            cursorPos = mf->makePoint(newX, cursorPos->getY(), cursorPos->getZ());
        }

        // X -> East
        Point::value maxX = gd->getScreenOffsetX() + screenToRegion(gd->getScreenWidth(), gd->getTileWidth());
        if (undoX < 0 && cursorPos->getX() < maxX)
        {
            auto newX = std::min(cursorPos->getX() - undoX, maxX - 1);
            cursorPos = mf->makePoint(newX, cursorPos->getY(), cursorPos->getZ());
        }
    }

    if (lastY)
    {
        // Y -> North
        if (undoY > 0 && cursorPos->getY() > gd->getScreenOffsetY())
        {
            auto newY = std::max(cursorPos->getY() - undoY, 0);
            cursorPos = mf->makePoint(cursorPos->getX(), newY, cursorPos->getZ());
        }

        // Y -> South
        Point::value maxY = gd->getScreenOffsetY() + screenToRegion(gd->getScreenHeight(), gd->getTileHeight());
        if (undoY < 0 && cursorPos->getY() < maxY)
        {
            auto newY = std::min(cursorPos->getY() - undoY, maxY - 1);
            cursorPos = mf->makePoint(cursorPos->getX(), newY, cursorPos->getZ());
        }
    }

    if (lastZ)
    {
        // Z -> Up/Down
        if (undoZ != 0)
        {
            cursorPos = mf->makePoint(cursorPos->getX(), cursorPos->getY(), cursorPos->getZ() + undoZ);
        }
    }

    lastX = lastY = lastZ = false;

    rm->setPos(gd->getCursor(), cursorPos, shared);
}
