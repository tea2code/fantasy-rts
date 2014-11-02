#include "VanillaSdl2Plugin.h"

#include "Sdl2Ids.h"
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
    frts::ModulePtr result = nullptr;
    if (id->toString() == Sdl2Ids::sdl2Renderer())
    {
        result = makeSdl2Renderer();
    }
    else if (id->toString() == Sdl2Ids::eventHandler())
    {
        result = getEventHandler();
    }
    else if (id->toString() == Sdl2Ids::inputHandler())
    {
        result = makeInputHandler(getEventHandler());
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaSdl2Plugin)
