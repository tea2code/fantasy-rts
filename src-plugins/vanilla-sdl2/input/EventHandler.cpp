#include "EventHandler.h"

#include <frts/vanillacommand>


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
        }
    }
}
