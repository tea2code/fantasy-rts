#include "EventHandler.h"

#include <graphic/impl/GraphicUtility.h>
#include <graphic/GraphicData.h>
#include <main/Sdl2Ids.h>
#include <frts/vanillacommand>
#include <frts/vanillamodel>


frts::EventHandler::EventHandler()
    : BaseTickable("frts::EventHandler", 1, "frts::EventHandler", 1)
{
}

void frts::EventHandler::registerCommand(SDL_Keycode key, IdPtr commandId)
{
    keyCommands[key] = commandId;
}

void frts::EventHandler::tick(SharedManagerPtr shared)
{
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
                auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
                auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
                auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());
                Point::value x = screenToRegion(event.motion.x, gd->getTileWidth()) + gd->getScreenOffsetX();
                Point::value y = screenToRegion(event.motion.y, gd->getTileHeight()) + gd->getScreenOffsetY();
                auto newPos = mf->makePoint(x, y, gd->getZLevel());
                //rm->removeEntity(gd->getCursor(), shared);
                rm->setPos(gd->getCursor(), newPos, shared);
            }
            break;
        }
    }
}
