#include "Sdl2EventHandler.h"

#include "InputHandler.h"
#include "impl/CloseContextCommandBuilder.h"
#include "impl/SelectionDataImpl.h"
#include "impl/SelectionHelper.h"
#include "impl/SelectCommandBuilder.h"
#include <graphic/impl/GraphicUtility.h>
#include <graphic/GraphicData.h>
#include <main/Sdl2Ids.h>
#include <frts/vanillacommand>
#include <frts/vanillamodel>
#include <frts/vanillaevent>
#include <frts/timer.h>


frts::Sdl2EventHandler::Sdl2EventHandler()
    : BaseTickable(Sdl2Ids::sdl2EventHandler(), 1, Sdl2Ids::sdl2EventHandler(), 1)
{
}

void frts::Sdl2EventHandler::checkRequiredData(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateDataValue(getName(), Sdl2Ids::graphicData(), 4, shared);
    validateDataValue(getName(), Sdl2Ids::selectionData(), 1, shared);
}

void frts::Sdl2EventHandler::closeCurrentContext()
{
    if (contextStack.top() != defaultContext)
    {
        contextStack.pop();
    }
}

bool frts::Sdl2EventHandler::createData(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto sd = makeSelectionData();
    auto id = shared->makeId(Sdl2Ids::selectionData());
    shared->setDataValue(id, sd);

    return false;
}

std::vector<std::string> frts::Sdl2EventHandler::getSupportedConfig()
{
    return {"screen"};
}

bool frts::Sdl2EventHandler::init(SharedManagerPtr shared)
{
    auto commandFactory = getUtility<CommandFactory>(shared, CommandIds::commandFactory());
    if (!commandFactory->isInitialized())
    {
        return true;
    }

    auto inputHandler = getUtility<Module>(shared, Sdl2Ids::inputHandler());
    if (!inputHandler->isInitialized())
    {
        return true;
    }

    // Add select command.
    IdPtr commandId = shared->makeId(Sdl2Ids::selectCommand());
    commandFactory->registerCommandBuilder(commandId, makeSelectCommandBuilder(commandId));

    // Add close context command.
    commandId = shared->makeId(Sdl2Ids::closeContextCommand());
    commandFactory->registerCommandBuilder(commandId, makeCloseContextCommandBuilder(commandId));

    // Check if input handler has initialized the default context.
    if (defaultContext == nullptr)
    {
        throw DataViolation(getName() + ": No default context provided.");
    }

    isInit = true;
    return false;
}

void frts::Sdl2EventHandler::parseConfig(const std::string&, ConfigNodePtr node, SharedManagerPtr shared)
{
    if (node->has("selection"))
    {
        auto id = shared->makeId(node->getString("selection"));

        auto sd = getDataValue<SelectionData>(shared, Sdl2Ids::selectionData());
        sd->setSelectionEntityId(id);
    }
}

void frts::Sdl2EventHandler::registerCommand(Sdl2KeyCommand keyCommand, IdPtr commandId)
{
    assert(commandId != nullptr);

    CommandContextChange ccc;
    ccc.command = commandId;
    keyCommands[keyCommand] = ccc;
}

void frts::Sdl2EventHandler::registerContextChange(Sdl2KeyCommand keyCommand, IdPtr context)
{
    assert(context != nullptr);

    CommandContextChange ccc;
    ccc.contextChange = context;
    keyCommands[keyCommand] = ccc;
}

void frts::Sdl2EventHandler::setDefaultContext(IdPtr context)
{
    defaultContext = context;
    while(!contextStack.empty())
    {
        contextStack.pop();
    }
    contextStack.push(context);
}

void frts::Sdl2EventHandler::tick(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    bool mouseMoved = false;
    SDL_Event mouseMoveEvent;

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
                // First with current context.
                Sdl2KeyCommand keyCommand = {
                    event.key.keysym.sym,
                    event.key.keysym.mod & KMOD_ALT,
                    event.key.keysym.mod & KMOD_CTRL,
                    event.key.keysym.mod & KMOD_SHIFT,
                    contextStack.top()
                };
                auto it = keyCommands.find(keyCommand);

                // If nothing is found try again without current context.
                if (it == keyCommands.end())
                {
                    keyCommand.context = nullptr;
                    it = keyCommands.find(keyCommand);
                }

                // Anything found?
                if (it != keyCommands.end())
                {
                    CommandContextChange ccc = it->second;
                    if (ccc.command != nullptr)
                    {
                        auto commandFactory = getUtility<CommandFactory>(shared, CommandIds::commandFactory());
                        auto command = commandFactory->makeCommand(ccc.command, shared);
                        command->execute(shared);
                        commandFactory->addToUndo(command, shared);
                    }
                    else
                    {
                        contextStack.push(ccc.contextChange);
                    }
                }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            {
                auto sd = getDataValue<SelectionData>(shared, Sdl2Ids::selectionData());
                auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());

                if (sd->isSelecting())
                {
                    continue;
                }

                // Create selections only in map area.
                auto mapArea = gd->getMapArea();
                auto mapPixelX = event.button.x - mapArea.x;
                auto mapPixelY = event.button.y - mapArea.y;
                if (!mapArea.isPixelInRect(mapPixelX, mapPixelY))
                {
                    return;
                }

                newSelection(shared);
            }
            break;

            case SDL_MOUSEBUTTONUP:
            {
                auto sd = getDataValue<SelectionData>(shared, Sdl2Ids::selectionData());

                if (sd->isSelecting())
                {
                    endSelection(shared);
                }
            }
            break;

            case SDL_MOUSEMOTION:
            {
                mouseMoved = true;
                mouseMoveEvent = event;
            }
            break;
        }
    }

    // Only handle last mouse movement.
    #pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
    if (mouseMoved)
    {
        PerformanceLog pl(getName() + " MouseMotion", shared, 5);

        auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
        auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());
        auto sd = getDataValue<SelectionData>(shared, Sdl2Ids::selectionData());
        auto rm = getDataValue<RegionManager>(shared, ModelIds::regionManager());

        // Set cursor position based on mouse event then update region and screen.
        // Important: The map area on the screen must be considered.
        auto mapArea = gd->getMapArea();
        auto mapPixelX = mouseMoveEvent.motion.x - mapArea.x;
        auto mapPixelY = mouseMoveEvent.motion.y - mapArea.y;
        if (!mapArea.isPixelInRect(mapPixelX, mapPixelY))
        {
            return;
        }

        Point::value x = screenToRegion(mapPixelX, gd->getTileWidth()) + gd->getScreenOffsetX();
        Point::value y = screenToRegion(mapPixelY, gd->getTileHeight()) + gd->getScreenOffsetY();
        auto newPos = mf->makePoint(x, y, gd->getZLevel());
        auto oldPos = rm->setPos(gd->getCursor(), newPos, shared);

        if (newPos == oldPos)
        {
            return;
        }
        raiseMoveCursorEvent(newPos, shared);

        if (sd->isSelecting())
        {
            updateSelection(newPos, shared);
        }
    }
}

void frts::Sdl2EventHandler::validateModules(frts::SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateUtility(getName(), ModelIds::modelFactory(), 2, shared);
    validateUtility(getName(), CommandIds::commandFactory(), 1, shared);
}
