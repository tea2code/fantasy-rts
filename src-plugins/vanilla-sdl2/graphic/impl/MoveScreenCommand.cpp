#include "MoveScreenCommand.h"

#include "GraphicUtility.h"
#include <graphic/GraphicData.h>
#include <main/Sdl2Ids.h>
#include <input/SelectionData.h>
#include <input/impl/SelectionHelper.h>

#include <algorithm>


frts::MoveScreenCommand::MoveScreenCommand(const IdPtr& commandType, Point::value x, Point::value y, Point::value z)
    : commandType{commandType}, x{x}, y{y}, z{z}
{}

void frts::MoveScreenCommand::execute(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    lastX = lastY = lastZ = false;

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto md = getDataValue<ModelData>(shared, ModelIds::modelData());
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
    auto mapArea = gd->getMapArea();

    // Old cursor position without offset.
    auto cursorPos = rm->getPos(gd->getCursor(), shared);
    cursorPos = mf->makePoint(cursorPos->getX() - gd->getScreenOffsetX(),
                              cursorPos->getY() - gd->getScreenOffsetY(),
                              cursorPos->getZ());

    // X -> West
    if (x > 0 && gd->getScreenOffsetX() > 0)
    {
        auto offset = std::max(gd->getScreenOffsetX() - x, 0);
        gd->setScreenOffsetX(offset);
        lastX = true;
    }

    // X -> East
    Point::value maxX = md->getMapSizeX() - pixelToTilesX(mapArea.width, shared);
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
    Point::value maxY = md->getMapSizeY() - pixelToTilesY(mapArea.height, shared);
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

        // Update cursor.
        cursorPos = mf->makePoint(cursorPos->getX() + gd->getScreenOffsetX(),
                                  cursorPos->getY() + gd->getScreenOffsetY(),
                                  gd->getZLevel());
        rm->setPos(gd->getCursor(), cursorPos, shared);
        raiseMoveCursorEvent(cursorPos, shared);

        // Update selection?
        try
        {
            auto sd = getDataValue<SelectionData>(shared, Sdl2Ids::selectionData());

            if (sd->isSelecting())
            {
                updateSelection(cursorPos, shared);
            }
        }
        catch(const IdNotFoundError&)
        {
            // Ignore. Seems like another input handler is used.
        }
    }
}

frts::IdPtr frts::MoveScreenCommand::getCommandType() const
{
    return commandType;
}

void frts::MoveScreenCommand::undo(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    auto md = getDataValue<ModelData>(shared, ModelIds::modelData());
    auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
    auto mapArea = gd->getMapArea();

    // Old cursor position without offset.
    auto cursorPos = rm->getPos(gd->getCursor(), shared);
    cursorPos = mf->makePoint(cursorPos->getX() - gd->getScreenOffsetX(),
                              cursorPos->getY() - gd->getScreenOffsetY(),
                              cursorPos->getZ());

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
        }

        // X -> East
        Point::value maxX = md->getMapSizeX() - pixelToTilesX(mapArea.width, shared);
        if (undoX < 0 && gd->getScreenOffsetX() < maxX)
        {
            auto offset = std::min(gd->getScreenOffsetX() - undoX, maxX);
            gd->setScreenOffsetX(offset);
        }
    }

    if (lastY)
    {
        // Y -> North
        if (undoY > 0 && gd->getScreenOffsetY() > 0)
        {
            auto offset = std::max(gd->getScreenOffsetY() - undoY, 0);
            gd->setScreenOffsetY(offset);
        }

        // Y -> South
        Point::value maxY = md->getMapSizeY() - pixelToTilesY(mapArea.height, shared);
        if (undoY < 0 && gd->getScreenOffsetY() < maxY)
        {
            auto offset = std::min(gd->getScreenOffsetY() - undoY, maxY);
            gd->setScreenOffsetY(offset);
        }
    }

    if (lastZ)
    {
        // Z -> Up/Down
        if (undoZ != 0)
        {
            gd->setZLevel(gd->getZLevel() + undoZ);
        }
    }

    lastX = lastY = lastZ = false;

    gd->setRenderEverything(true);

    // Update cursor.
    cursorPos = mf->makePoint(cursorPos->getX() + gd->getScreenOffsetX(),
                              cursorPos->getY() + gd->getScreenOffsetY(),
                              gd->getZLevel());
    rm->setPos(gd->getCursor(), cursorPos, shared);
    raiseMoveCursorEvent(cursorPos, shared);
}
