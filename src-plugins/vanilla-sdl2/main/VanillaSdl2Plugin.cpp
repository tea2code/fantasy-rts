#include "VanillaSdl2Plugin.h"

#include <graphic/Sdl2Renderer.h>
#include <input/EventHandler.h>
#include <input/impl/InputHandlerImpl.h>

#include <frts/shared>

#include <memory>


frts::VanillaSdl2Plugin::VanillaSdl2Plugin()
{
}

frts::EventHandlerPtr frts::VanillaSdl2Plugin::getEventHandler()
{
    if (eventHandler == nullptr)
    {
        eventHandler = makeEventHandler();
    }
    return eventHandler;
}

frts::ModulePtr frts::VanillaSdl2Plugin::getModule(frts::IdPtr id)
{
    assert(id != nullptr);

    frts::ModulePtr result = nullptr;
    if (id->toString() == Sdl2Renderer::identifier())
    {
        result = makeSdl2Renderer();
    }
    else if (id->toString() == EventHandler::identifier())
    {
        result = getEventHandler();
    }
    else if (id->toString() == InputHandlerImpl::identifier())
    {
        result = makeInputHandler(getEventHandler());
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaSdl2Plugin)
