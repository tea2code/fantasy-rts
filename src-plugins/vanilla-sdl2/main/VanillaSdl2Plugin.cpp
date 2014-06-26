#include "VanillaSdl2Plugin.h"

#include "VanillaSdl2Tickable.h"
#include <input/impl/EventHandlerImpl.h>

#include <frts/shared>

#include <memory>


frts::VanillaSdl2Plugin::VanillaSdl2Plugin()
{
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
        result = makeEventHandler();
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaSdl2Plugin)
