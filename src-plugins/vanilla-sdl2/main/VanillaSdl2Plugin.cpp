#include "VanillaSdl2Plugin.h"

#include "VanillaSdl2Tickable.h"
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
    if (id->toString() == module)
    {
        result = std::make_shared<VanillaSdl2Tickable>();
    }
    else if (id->toString() == eventModule)
    {
        result = getEventHandler();
    }
    else if (id->toString() == inputModule)
    {
        result = makeInputHandler(getEventHandler());
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaSdl2Plugin)