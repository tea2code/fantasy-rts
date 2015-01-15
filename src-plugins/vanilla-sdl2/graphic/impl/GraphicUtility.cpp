#include "GraphicUtility.h"

#include <graphic/GraphicData.h>
#include <main/Sdl2Ids.h>
#include <frts/vanillaevent>


void frts::raiseMoveCursorEvent(PointPtr cursorPos, SharedManagerPtr shared)
{
    auto em = getUtility<EventManager>(shared, EventIds::eventManager());
    auto event = em->makeEvent(shared->makeId(Sdl2Ids::moveCursorEvent()), shared);
    auto eventValue = makeEventValue<PointEventValue>(em, ModelEventIds::pointEventValue(), shared);
    eventValue->setValue(cursorPos);
    event->setValue(shared->makeId(Sdl2Ids::moveCursorEventPos()), eventValue);
    em->raise(event, shared);
}

frts::Point::value frts::screenToRegion(GraphicData::pixel screen, GraphicData::pixel tile)
{
    return static_cast<Point::value>(screen / tile);
}


frts::GraphicData::pixel frts::regionToScreen(Point::value region, GraphicData::pixel tile)
{
    return static_cast<GraphicData::pixel>(region) * tile;
}
