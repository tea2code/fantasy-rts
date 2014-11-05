#include "InputHandlerImpl.h"

#include <input/KeyToSdl2Key.h>
#include <input/StringToSdl2Key.h>
#include <main/Sdl2Ids.h>

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
    return Sdl2Ids::inputHandler();
}

std::vector<std::string> frts::InputHandlerImpl::getSupportedConfig()
{
    return {configKey};
}

std::string frts::InputHandlerImpl::getTypeName() const
{
    return getName();
}

int frts::InputHandlerImpl::getTypeVersion() const
{
    return 1;
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
    auto commandFactory = getUtility<CommandFactory>(shared, CommandIds::commandFactory());
    for (auto node : configNodes)
    {
        for (auto keyNode : *node)
        {
            auto key = keyNode->getString("key");
            auto id = shared->makeId(keyNode->getString("command"));
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
        auto id = shared->makeId(CommandIds::commandFactory());
        shared->getUtility(id);
    }
    catch(const IdNotFoundError&)
    {
        throw ModuleViolation("Utility CommandFactory not found.");
    }

    // EventHandler.
    const std::string eventHandlerType = "frts::EventHandler";
    bool found = false;
    for (auto it = shared->updateModulesBegin(); it != shared->updateModulesEnd(); ++it)
    {
        if ((*it)->getTypeName() == eventHandlerType)
        {
            found = true;
            break;
        }
    }
    for (auto it = shared->renderModulesBegin(); it != shared->renderModulesEnd(); ++it)
    {
        if ((*it)->getTypeName() == eventHandlerType)
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
