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
    return static_cast<Point::value>(pixel / (gd->getTileWidth() * gd->getZoom()));
}

frts::Point::value frts::pixelToTilesY(GraphicData::pixel pixel, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    return static_cast<Point::value>(pixel / (gd->getTileHeight() * gd->getZoom()));
}

frts::GraphicData::pixel frts::regionToScreenX(Point::value pos, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    return tilesToPixelX(pos - gd->getScreenOffsetX(), shared);
}

frts::GraphicData::pixel frts::regionToScreenY(Point::value pos, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    return tilesToPixelY(pos - gd->getScreenOffsetY(), shared);
}

frts::Point::value frts::screenToRegionX(GraphicData::pixel pixel, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    return pixelToTilesX(pixel, shared) + gd->getScreenOffsetX();
}

frts::Point::value frts::screenToRegionY(GraphicData::pixel pixel, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    return pixelToTilesY(pixel, shared) + gd->getScreenOffsetY();
}

frts::GraphicData::pixel frts::tilesToPixelX(Point::value tiles, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    return static_cast<GraphicData::pixel>(tiles) *
           static_cast<GraphicData::pixel>(gd->getTileWidth() * gd->getZoom());
}

frts::GraphicData::pixel frts::tilesToPixelY(Point::value tiles, const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
    return static_cast<GraphicData::pixel>(tiles) *
           static_cast<GraphicData::pixel>(gd->getTileHeight() * gd->getZoom());
}
