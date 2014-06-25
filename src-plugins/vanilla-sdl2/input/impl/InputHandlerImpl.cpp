#include "InputHandlerImpl.h"

#include <input/KeyToSdl2Key.h>
#include <input/StringToSdl2Key.h>

#include <frts/configuration>


frts::InputHandlerImpl::InputHandlerImpl()
{
}

bool frts::InputHandlerImpl::createData(SharedManagerPtr)
{
    return false;
}

std::string frts::InputHandlerImpl::getName() const
{
    return "frts::InputHandler";
}

std::vector<std::string> frts::InputHandlerImpl::getSupportedConfig()
{
    return {configKey};
}

int frts::InputHandlerImpl::getVersion() const
{
    return 1;
}

bool frts::InputHandlerImpl::init(SharedManagerPtr)
{
    return false;
}

void frts::InputHandlerImpl::registerCommand(Key key, CommandPtr command)
{
    keyCommands[keyToSdl2Key(key)] = command;
}

void frts::InputHandlerImpl::parseConfig(const std::string&, ConfigNodePtr node, SharedManagerPtr shared)
{
    IdPtr id = shared->makeId("frts/CommandFactory");
    CommandFactoryPtr commandFactory = std::static_pointer_cast<CommandFactory>(shared->getUtility(id));

    for (auto keyNode : *node)
    {
        std::string key = keyNode->getString("key");
        IdPtr id = shared->makeId(keyNode->getString("command"));
        keyCommands[stringToSdl2Key(key)] = commandFactory->makeCommand(id, shared);
    }
}

bool frts::InputHandlerImpl::preInit(SharedManagerPtr)
{
    return false;
}

void frts::InputHandlerImpl::tick(SharedManagerPtr)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            shared->setQuitApplication(true);
        }
    }
}

void frts::InputHandlerImpl::validateData(SharedManagerPtr)
{

}

void frts::InputHandlerImpl::validateModules(SharedManagerPtr shared)
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
