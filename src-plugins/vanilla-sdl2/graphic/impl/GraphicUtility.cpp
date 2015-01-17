#include "GraphicUtility.h"

#include <graphic/GraphicData.h>
#include <main/Sdl2Ids.h>
#include <frts/vanillaevent>


void frts::raiseMoveCursorEvent(const PointPtr& cursorPos, const SharedManagerPtr& shared)
{
    assert(cursorPos != nullptr);
    assert(shared != nullptr);

    auto em = getUtility<EventManager>(shared, EventIds::eventManager());
    auto event = em->makeEvent(shared->makeId(Sdl2Ids::moveCursorEvent()), shared);
    auto eventValue = makeEventValue<PointEventValue>(em, ModelEventIds::pointEventValue(), shared);
    eventValue->setValue(cursorPos);
    event->setValue(shared->makeId(Sdl2Ids::moveCursorEventPos()), eventValue);
    em->raise(event, shared);
}

frts::Point::value frts::pixelToTilesX(GraphicData::pixel pixel, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    return static_cast<Point::value>(pixel / gd->getTileWidth());
}

frts::Point::value frts::pixelToTilesY(GraphicData::pixel pixel, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    return static_cast<Point::value>(pixel / gd->getTileHeight());
}

frts::GraphicData::pixel frts::tilesToPixelX(Point::value tiles, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    return static_cast<GraphicData::pixel>(tiles) * gd->getTileWidth();
}

frts::GraphicData::pixel frts::tilesToPixelY(Point::value tiles, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    return static_cast<GraphicData::pixel>(tiles) * gd->getTileHeight();
}
