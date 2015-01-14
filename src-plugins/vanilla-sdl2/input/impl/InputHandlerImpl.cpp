#include "InputHandlerImpl.h"

#include <input/KeyToSdl2Key.h>
#include <input/StringToSdl2Key.h>
#include <main/Sdl2Ids.h>

#include <frts/configuration>

#include <boost/format.hpp>


frts::InputHandlerImpl::InputHandlerImpl(Sdl2EventHandlerPtr sdl2EventHandler)
    : sdl2EventHandler{sdl2EventHandler}
{
}

void frts::InputHandlerImpl::checkRequiredData(SharedManagerPtr)
{}

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
    assert(shared != nullptr);

    auto commandFactory = getUtility<CommandFactory>(shared, CommandIds::commandFactory());
    if (!commandFactory->isInitialized())
    {
        return true;
    }

    // Initialize commands from configuration.
    for (auto node : configNodes)
    {
        if (node->has("default_context"))
        {
            sdl2EventHandler->setDefaultContext(shared->makeId(node->getString("default_context")));
        }

        auto keyNodes = node->getNode("keys");
        for (auto keyNode : *keyNodes)
        {
            auto key = keyNode->getString("key");
            auto alt = keyNode->getBool("alt", false);
            auto ctrl = keyNode->getBool("ctrl", false);
            auto shift = keyNode->getBool("shift", false);
            IdPtr context;
            if (keyNode->has("context"))
            {
                context = shared->makeId(keyNode->getString("context"));
            }

            Sdl2KeyCommand sdl2KeyCommand =
            {
                stringToSdl2Key(key),
                alt,
                ctrl,
                shift,
                context
            };

            if (keyNode->has("command"))
            {
                auto id = shared->makeId(keyNode->getString("command"));
                sdl2EventHandler->registerCommand(sdl2KeyCommand, id);
            }
            else if (keyNode->has("set_context"))
            {
                auto id = shared->makeId(keyNode->getString("set_context"));
                sdl2EventHandler->registerContextChange(sdl2KeyCommand, id);
            }
            else
            {
                auto msg = boost::format(R"(No command or context set for key "%1%".)") % key;
                shared->getLog()->warning(getName(), msg.str());
            }
        }
    }
    configNodes.clear();

    isInit = true;
    return false;
}

bool frts::InputHandlerImpl::isInitialized() const
{
    return isInit;
}

bool frts::InputHandlerImpl::isPreInitialized() const
{
    return isPreInit;
}

void frts::InputHandlerImpl::registerCommand(KeyCommand keyCommand, IdPtr commandId)
{
    Sdl2KeyCommand sdl2KeyCommand =
    {
        keyToSdl2Key(keyCommand.key),
        keyCommand.alt,
        keyCommand.ctrl,
        keyCommand.shift
    };
    sdl2EventHandler->registerCommand(sdl2KeyCommand, commandId);
}

void frts::InputHandlerImpl::parseConfig(const std::string&, ConfigNodePtr node, SharedManagerPtr)
{
    assert(node != nullptr);

    // Store for initialization.
    configNodes.push_back(node);
}

bool frts::InputHandlerImpl::preInit(SharedManagerPtr)
{
    isPreInit = true;
    return false;
}

void frts::InputHandlerImpl::validateData(SharedManagerPtr)
{

}

void frts::InputHandlerImpl::validateModules(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateUtility(getName(), CommandIds::commandFactory(), 1, shared);
    validateTickable(getName(), Sdl2Ids::sdl2EventHandler(), 1, shared);
}
