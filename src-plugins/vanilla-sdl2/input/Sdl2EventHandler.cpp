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
#include <frts/math.h>
#include <frts/timer.h>


frts::Sdl2EventHandler::Sdl2EventHandler()
    : BaseTickable(Sdl2Ids::sdl2EventHandler(), 2, Sdl2Ids::sdl2EventHandler(), 2)
{
}

void frts::Sdl2EventHandler::checkRequiredData(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    validateDataValue(getName(), Sdl2Ids::graphicData(), 4, shared);
    validateDataValue(getName(), Sdl2Ids::selectionData(), 1, shared);
}

void frts::Sdl2EventHandler::closeContext(bool resetToDefault)
{
    bool reset = true;
    while (reset && (contextStack.top() != defaultContext))
    {
        contextStack.pop();
        reset = resetToDefault;
    }
}

bool frts::Sdl2EventHandler::createData(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto sd = makeSelectionData();
    auto id = shared->makeId(Sdl2Ids::selectionData());
    shared->setDataValue(id, sd);

    return false;
}

void frts::Sdl2EventHandler::executeCommandContextChange(const CommandContextChange& ccc, const SharedManagerPtr& shared)
{
    if (ccc.command != nullptr)
    {
        auto commandFactory = getUtility<CommandFactory>(shared, CommandIds::commandFactory());
        auto command = commandFactory->makeCommand(ccc.command, shared);
        command->execute(shared);
        commandFactory->addToUndo(command, shared);
    }
    if (ccc.contextChange != nullptr)
    {
        contextStack.push(ccc.contextChange);
    }
}

std::vector<std::string> frts::Sdl2EventHandler::getSupportedConfig()
{
    return {"screen"};
}

bool frts::Sdl2EventHandler::init(const SharedManagerPtr& shared)
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

    // Add close context commands.
    commandId = shared->makeId(Sdl2Ids::closeContextCommand());
    commandFactory->registerCommandBuilder(commandId, makeCloseContextCommandBuilder(commandId, false));
    commandId = shared->makeId(Sdl2Ids::closeAllContextCommand());
    commandFactory->registerCommandBuilder(commandId, makeCloseContextCommandBuilder(commandId, true));

    // Check if input handler has initialized the default context.
    if (defaultContext == nullptr)
    {
        throw DataViolation(getName() + ": No default context provided.");
    }

    return BaseTickable::init(shared);
}

void frts::Sdl2EventHandler::parseConfig(const std::string&, const ConfigNodePtr& node, const SharedManagerPtr& shared)
{
    if (node->has("selection"))
    {
        auto id = shared->makeId(node->getString("selection"));

        auto sd = getDataValue<SelectionData>(shared, Sdl2Ids::selectionData());
        sd->setSelectionEntityId(id);
    }
}

void frts::Sdl2EventHandler::registerCommand(const Sdl2ButtonCommand<SDL_Keycode>& keyCommand, const IdPtr& commandId)
{
    assert(commandId != nullptr);

    CommandContextChange ccc;
    ccc.command = commandId;
    keyCommands[keyCommand] = ccc;
}

void frts::Sdl2EventHandler::registerCommand(const Sdl2ButtonCommand<std::uint8_t>& mouseButtonCommand, const IdPtr& commandId)
{
    assert(commandId != nullptr);

    CommandContextChange ccc;
    ccc.command = commandId;
    mouseButtonsCommands[mouseButtonCommand] = ccc;
}

void frts::Sdl2EventHandler::registerContextChange(const Sdl2ButtonCommand<SDL_Keycode>& keyCommand, const IdPtr& context)
{
    assert(context != nullptr);

    CommandContextChange ccc;
    ccc.contextChange = context;
    keyCommands[keyCommand] = ccc;
}

void frts::Sdl2EventHandler::registerContextChange(const Sdl2ButtonCommand<std::uint8_t>& mouseButtonCommand, const IdPtr& context)
{
    assert(context != nullptr);

    CommandContextChange ccc;
    ccc.contextChange = context;
    mouseButtonsCommands[mouseButtonCommand] = ccc;
}

void frts::Sdl2EventHandler::setDefaultContext(const IdPtr& context)
{
    defaultContext = context;
    while(!contextStack.empty())
    {
        contextStack.pop();
    }
    contextStack.push(context);
}

void frts::Sdl2EventHandler::tick(const SharedManagerPtr& shared)
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
                Sdl2ButtonCommand<SDL_Keycode> keyCommand = {
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
                    executeCommandContextChange(it->second, shared);
                }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            {
                // Check if a known mouse button is pressed and execute the corresponding command.
                // First with current context.
                auto keyMod = SDL_GetModState();
                Sdl2ButtonCommand<std::uint8_t> mouseButtonCommand = {
                    event.button.button,
                    keyMod & KMOD_ALT,
                    keyMod & KMOD_CTRL,
                    keyMod & KMOD_SHIFT,
                    contextStack.top()
                };
                auto it = mouseButtonsCommands.find(mouseButtonCommand);

                // If nothing is found try again without current context.
                if (it == mouseButtonsCommands.end())
                {
                    mouseButtonCommand.context = nullptr;
                    it = mouseButtonsCommands.find(mouseButtonCommand);
                }

                // Anything found?
                if (it != mouseButtonsCommands.end())
                {
                    executeCommandContextChange(it->second, shared);
                }
                // If nothing was found simple start a selection.
                else
                {
                    auto sd = getDataValue<SelectionData>(shared, Sdl2Ids::selectionData());
                    auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());

                    if (sd->isSelecting())
                    {
                        continue;
                    }

                    // Create selections only in map area.
                    auto mapArea = gd->getMapArea();
                    auto mapPixelX = static_cast<GraphicData::pixel>(event.button.x) - mapArea.x;
                    auto mapPixelY = static_cast<GraphicData::pixel>(event.button.y) - mapArea.y;
                    if (!mapArea.isPixelInRect(mapPixelX, mapPixelY))
                    {
                        return;
                    }

                    newSelection(shared);
                }
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

            case SDL_MOUSEWHEEL:
            {
                auto y = event.wheel.y;
                if (y == 0)
                {
                    break;
                }

                auto gd = getDataValue<GraphicData>(shared, Sdl2Ids::graphicData());

                // Search current zoom level manually.
                auto currentZoom = gd->getZoom();
                auto zoomLevels = gd->getZoomLevels();
                int currentIndex = 0;
                for (size_t i = 0; i < zoomLevels.size(); ++i)
                {
                    if (floatEqual(currentZoom, zoomLevels.at(i)))
                    {
                        currentIndex = static_cast<int>(i);
                        break;
                    }
                }

                // Away from the user.
                if (y > 0)
                {
                    currentIndex = std::min(currentIndex + 1, static_cast<int>(zoomLevels.size() - 1));
                }
                // Towards the user.
                else
                {
                    currentIndex = std::max(currentIndex - 1, 0);
                }

                gd->setRenderEverything();
                gd->setScreenOffsetX(0);
                gd->setScreenOffsetY(0);
                gd->setZoom(zoomLevels.at(static_cast<size_t>(currentIndex)));
            }
            break;

            default:
            // Rest we don't care.
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
        auto mapPixelX = static_cast<GraphicData::pixel>(mouseMoveEvent.motion.x) - mapArea.x;
        auto mapPixelY = static_cast<GraphicData::pixel>(mouseMoveEvent.motion.y) - mapArea.y;
        if (!mapArea.isPixelInRect(mapPixelX, mapPixelY))
        {
            return;
        }

        Point::value x = screenToRegionX(mapPixelX, shared);
        Point::value y = screenToRegionY(mapPixelY, shared);
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

void frts::Sdl2EventHandler::validateModules(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    validateUtility(getName(), ModelIds::modelFactory(), 2, shared);
    validateUtility(getName(), CommandIds::commandFactory(), 1, shared);
}
