#include "EventHandlerImpl.h"

#include <input/KeyToSdl2Key.h>
#include <input/StringToSdl2Key.h>

#include <frts/configuration>


frts::EventHandlerImpl::EventHandlerImpl()
{
}

bool frts::EventHandlerImpl::createData(SharedManagerPtr)
{
    return false;
}

std::string frts::EventHandlerImpl::getName() const
{
    return "frts::EventHandler";
}

std::vector<std::string> frts::EventHandlerImpl::getSupportedConfig()
{
    return {configKey};
}

int frts::EventHandlerImpl::getVersion() const
{
    return 1;
}

bool frts::EventHandlerImpl::init(SharedManagerPtr shared)
{
    // Request another initalization round to allow initialization of command factory
    // happen first.
    if (firstInit)
    {
        firstInit = false;
        return true;
    }

    // Initialize commands from configuration.
    IdPtr id = shared->makeId("frts/CommandFactory");
    CommandFactoryPtr commandFactory = std::static_pointer_cast<CommandFactory>(shared->getUtility(id));
    for (auto node : configNodes)
    {
        for (auto keyNode : *node)
        {
            std::string key = keyNode->getString("key");
            IdPtr id = shared->makeId(keyNode->getString("command"));
            keyCommands[stringToSdl2Key(key)] = commandFactory->makeCommand(id, shared);
        }
    }
    configNodes.clear();

    return false;
}

void frts::EventHandlerImpl::registerCommand(Key key, CommandPtr command)
{
    keyCommands[keyToSdl2Key(key)] = command;
}

void frts::EventHandlerImpl::parseConfig(const std::string&, ConfigNodePtr node, SharedManagerPtr)
{
    // Store for initialization.
    configNodes.push_back(node);
}

bool frts::EventHandlerImpl::preInit(SharedManagerPtr)
{
    return false;
}

void frts::EventHandlerImpl::tick(SharedManagerPtr shared)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            shared->setQuitApplication(true);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            SDL_Keycode key = event.key.keysym.sym;
            auto it = keyCommands.find(key);
            if (it != keyCommands.end())
            {
                it->second->execute(shared);
            }
        }
    }
}

void frts::EventHandlerImpl::validateData(SharedManagerPtr)
{

}

void frts::EventHandlerImpl::validateModules(SharedManagerPtr shared)
{
    try
    {
        IdPtr id = shared->makeId("frts/CommandFactory");
        shared->getUtility(id);
    }
    catch(const IdNotFoundError&)
    {
        throw ModuleViolation("Utility CommandFactory not found.");
    }
}
