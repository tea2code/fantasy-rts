#include "InputHandlerImpl.h"

#include <input/KeyToSdl2Key.h>
#include <input/MouseButtonToSdl2MouseButton.h>
#include <input/StringToSdl2Key.h>
#include <input/StringToSdl2MouseButton.h>
#include <main/Sdl2Ids.h>
#include <frts/configuration>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/format.hpp>

#include <algorithm>


frts::InputHandlerImpl::InputHandlerImpl(const Sdl2EventHandlerPtr& sdl2EventHandler)
    : BaseUtility(Sdl2Ids::inputHandler(), 2, Sdl2Ids::inputHandler(), 2),
      sdl2EventHandler{sdl2EventHandler}
{
}

void frts::InputHandlerImpl::closeCurrentContext()
{
    sdl2EventHandler->closeCurrentContext();
}

std::vector<std::string> frts::InputHandlerImpl::getSupportedConfig()
{
    return {"keys"};
}

void frts::InputHandlerImpl::registerCommand(const ButtonCommand<Key>& keyCommand, const IdPtr& commandId)
{
    assert(commandId != nullptr);

    Sdl2ButtonCommand<SDL_Keycode> sdl2KeyCommand =
    {
        keyToSdl2Key(keyCommand.button),
        keyCommand.alt,
        keyCommand.ctrl,
        keyCommand.shift,
        keyCommand.context
    };
    sdl2EventHandler->registerCommand(sdl2KeyCommand, commandId);
}

void frts::InputHandlerImpl::registerCommand(const ButtonCommand<MouseButton>& mouseButtonCommand, const IdPtr& commandId)
{
    assert(commandId != nullptr);

    Sdl2ButtonCommand<std::uint8_t> sdl2MouseButtonCommand =
    {
        mouseButtonToSdl2MouseButton(mouseButtonCommand.button),
        mouseButtonCommand.alt,
        mouseButtonCommand.ctrl,
        mouseButtonCommand.shift,
        mouseButtonCommand.context
    };
    sdl2EventHandler->registerCommand(sdl2MouseButtonCommand, commandId);
}

void frts::InputHandlerImpl::registerContextChange(const ButtonCommand<Key>& keyCommand, const IdPtr& context)
{
    assert(context != nullptr);

    Sdl2ButtonCommand<SDL_Keycode> sdl2KeyCommand =
    {
        keyToSdl2Key(keyCommand.button),
        keyCommand.alt,
        keyCommand.ctrl,
        keyCommand.shift,
        keyCommand.context
    };
    sdl2EventHandler->registerContextChange(sdl2KeyCommand, context);
}

void frts::InputHandlerImpl::registerContextChange(const ButtonCommand<MouseButton>& mouseButtonCommand, const IdPtr& context)
{
    assert(context != nullptr);

    Sdl2ButtonCommand<std::uint8_t> sdl2MouseButtonCommand =
    {
        mouseButtonToSdl2MouseButton(mouseButtonCommand.button),
        mouseButtonCommand.alt,
        mouseButtonCommand.ctrl,
        mouseButtonCommand.shift,
        mouseButtonCommand.context
    };
    sdl2EventHandler->registerContextChange(sdl2MouseButtonCommand, context);
}

void frts::InputHandlerImpl::parseConfig(const std::string&, const ConfigNodePtr& node, const SharedManagerPtr& shared)
{
    assert(node != nullptr);

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

        // Is the key a mouse button?
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        if (boost::starts_with(key, mouseButtonStringPrefix()))
        {
            Sdl2ButtonCommand<std::uint8_t> sdl2MouseButtonCommand =
            {
                stringToSdl2MouseButton(key),
                alt,
                ctrl,
                shift,
                context
            };

            if (keyNode->has("command"))
            {
                auto id = shared->makeId(keyNode->getString("command"));
                sdl2EventHandler->registerCommand(sdl2MouseButtonCommand, id);
            }
            else if (keyNode->has("set_context"))
            {
                auto id = shared->makeId(keyNode->getString("set_context"));
                sdl2EventHandler->registerContextChange(sdl2MouseButtonCommand, id);
            }
            else
            {
                auto msg = boost::format(R"(No command or context set for mouse button "%1%".)") % key;
                shared->getLog()->warning(getName(), msg.str());
            }
        }
        else
        {
            Sdl2ButtonCommand<SDL_Keycode> sdl2KeyCommand =
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
}

void frts::InputHandlerImpl::validateModules(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    validateUtility(getName(), CommandIds::commandFactory(), 1, shared);
    validateTickable(getName(), Sdl2Ids::sdl2EventHandler(), 2, shared);
}
