#include "Sdl2EventHandler.h"

#include <graphic/impl/GraphicUtility.h>
#include <graphic/GraphicData.h>
#include <main/Sdl2Ids.h>
#include <frts/vanillacommand>
#include <frts/vanillamodel>
#include <frts/vanillaevent>


frts::Sdl2EventHandler::Sdl2EventHandler()
    : BaseTickable("frts::Sdl2EventHandler", 1, "frts::Sdl2EventHandler", 1)
{
}

void frts::Sdl2EventHandler::checkRequiredData(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateDataValue(getName(), Sdl2Ids::graphicData(), 4, shared);
}

void frts::Sdl2EventHandler::registerCommand(SDL_Keycode key, IdPtr commandId)
{
    assert(commandId != nullptr);

    keyCommands[key] = commandId;
}

void frts::Sdl2EventHandler::tick(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
            {
                shared->setQuitApplication(true);
            }
            break;

            case SDL_KEYDOWN:
            {
                // Check if a known key is pressed and execute the corresponding command.
                auto key = event.key.keysym.sym;
                auto it = keyCommands.find(key);
                if (it != keyCommands.end())
                {
                    auto commandFactory = getUtility<CommandFactory>(shared, CommandIds::commandFactory());
                    auto command = commandFactory->makeCommand(it->second, shared);
                    command->execute(shared);
                    commandFactory->addToUndo(command, shared);
                }
            }
            break;

            case SDL_MOUSEMOTION:
            {
                // Set cursor position based on mouse event then update region and screen.
                // Important: The map area on the screen must be considered.

                auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
                auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
                auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());

                auto mapArea = gd->getMapArea();
                auto mapPixelX = event.motion.x - mapArea.x;
                auto mapPixelY = event.motion.y - mapArea.y;
                if (!mapArea.isPixelInRect(mapPixelX, mapPixelY))
                {
                    continue;
                }

                Point::value x = screenToRegion(mapPixelX, gd->getTileWidth()) + gd->getScreenOffsetX();
                Point::value y = screenToRegion(mapPixelY, gd->getTileHeight()) + gd->getScreenOffsetY();
                auto newPos = mf->makePoint(x, y, gd->getZLevel());
                auto oldPos = rm->setPos(gd->getCursor(), newPos, shared);

                if (newPos != oldPos)
                {
                    auto em = getUtility<EventManager>(shared, EventIds::eventManager());
                    auto event = em->makeEvent(shared->makeId(Sdl2Ids::eventMoveCursor()), shared);
                    auto eventValue = makeEventValue<PointEventValue>(em, ModelEventIds::pointEventValue(), shared);
                    eventValue->setValue(newPos);
                    event->setValue(shared->makeId(Sdl2Ids::eventMoveCursorPos()), eventValue);
                    em->raise(event, shared);
                }
            }
            break;
        }
    }
}

void frts::Sdl2EventHandler::validateModules(frts::SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateUtility(getName(), ModelIds::modelFactory(), 1, shared);
}
