#include "InputHandlerImpl.h"

#include <input/KeyToSdl2Key.h>
#include <input/StringToSdl2Key.h>

#include <frts/configuration>


frts::InputHandlerImpl::InputHandlerImpl(EventHandlerPtr eventHandler)
    : eventHandler{eventHandler}
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

bool frts::InputHandlerImpl::init(SharedManagerPtr shared)
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
            eventHandler->registerCommand(stringToSdl2Key(key), commandFactory->makeCommand(id, shared));
        }
    }
    configNodes.clear();

    return false;
}

void frts::InputHandlerImpl::registerCommand(Key key, CommandPtr command)
{
    eventHandler->registerCommand(keyToSdl2Key(key), command);
}

void frts::InputHandlerImpl::parseConfig(const std::string&, ConfigNodePtr node, SharedManagerPtr)
{
    // Store for initialization.
    configNodes.push_back(node);
}

bool frts::InputHandlerImpl::preInit(SharedManagerPtr)
{
    return false;
}

void frts::InputHandlerImpl::validateData(SharedManagerPtr)
{

}

void frts::InputHandlerImpl::validateModules(SharedManagerPtr shared)
{
    // CommandFactory.
    try
    {
        IdPtr id = shared->makeId("frts/CommandFactory");
        shared->getUtility(id);
    }
    catch(const IdNotFoundError&)
    {
        throw ModuleViolation("Utility CommandFactory not found.");
    }

    // EventHandler.
    const std::string eventHandlerName = "frts::EventHandler";
    bool found = false;
    for (auto it = shared->updateModulesBegin(); it != shared->updateModulesEnd(); ++it)
    {
        if ((*it)->getName() == eventHandlerName)
        {
            found = true;
            break;
        }
    }
    for (auto it = shared->renderModulesBegin(); it != shared->renderModulesEnd(); ++it)
    {
        if ((*it)->getName() == eventHandlerName)
        {
            found = true;
            break;
        }
    }
    if (!found)
    {
        throw ModuleViolation("Tickable EventHandler not found.");
    }
}
