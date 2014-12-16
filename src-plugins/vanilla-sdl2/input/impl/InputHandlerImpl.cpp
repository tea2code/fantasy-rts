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
    return {"keys"};
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
    for (auto& node : configNodes)
    {
        for (auto keyNode : *node)
        {
            auto key = keyNode->getString("key");
            auto id = shared->makeId(keyNode->getString("command"));
            eventHandler->registerCommand(stringToSdl2Key(key), id);
        }
    }
    configNodes.clear();

    return false;
}

void frts::InputHandlerImpl::registerCommand(Key key, IdPtr commandId)
{
    eventHandler->registerCommand(keyToSdl2Key(key), commandId);
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
    validateUtility(getName(), CommandIds::commandFactory(), 1, shared);
    validateTickable(getName(), "frts::EventHandler", 1, shared);
}
