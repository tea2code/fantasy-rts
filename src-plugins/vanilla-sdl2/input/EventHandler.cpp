#include "EventHandler.h"


frts::EventHandler::EventHandler()
{
}

bool frts::EventHandler::createData(SharedManagerPtr)
{
    return false;
}

std::string frts::EventHandler::getName() const
{
    return "frts::EventHandler";
}

std::vector<std::string> frts::EventHandler::getSupportedConfig()
{
    return {};
}

int frts::EventHandler::getVersion() const
{
    return 1;
}

bool frts::EventHandler::init(SharedManagerPtr)
{
    return false;
}

void frts::EventHandler::registerCommand(SDL_Keycode key, CommandPtr command)
{
    keyCommands[key] = command;
}

void frts::EventHandler::parseConfig(const std::string&, ConfigNodePtr, SharedManagerPtr)
{

}

bool frts::EventHandler::preInit(SharedManagerPtr)
{
    return false;
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
                    it->second->execute(shared);
                }
            }
            break;
        }
    }
}

void frts::EventHandler::validateData(SharedManagerPtr)
{

}

void frts::EventHandler::validateModules(SharedManagerPtr)
{

}
