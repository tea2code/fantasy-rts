#include "VanillaSdl2Plugin.h"

#include <graphic/Sdl2Renderer.h>
#include <input/Sdl2EventHandler.h>
#include <input/impl/InputHandlerImpl.h>

#include <frts/shared>

#include <memory>


frts::VanillaSdl2Plugin::VanillaSdl2Plugin()
{
}

frts::Sdl2EventHandlerPtr frts::VanillaSdl2Plugin::getSdl2EventHandler()
{
    if (sdl2EventHandler == nullptr)
    {
        sdl2EventHandler = makeSdl2EventHandler();
    }
    return sdl2EventHandler;
}

frts::ModulePtr frts::VanillaSdl2Plugin::getModule(const IdPtr& id)
{
    assert(id != nullptr);

    frts::ModulePtr result = nullptr;
    if (id->toString() == Sdl2Renderer::identifier())
    {
        result = makeSdl2Renderer();
    }
    else if (id->toString() == Sdl2EventHandler::identifier())
    {
        result = getSdl2EventHandler();
    }
    else if (id->toString() == InputHandlerImpl::identifier())
    {
        result = makeInputHandler(getSdl2EventHandler());
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaSdl2Plugin)
