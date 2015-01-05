#include "VanillaEventPlugin.h"

#include "impl/EventManagerImpl.h"


frts::VanillaEventPlugin::VanillaEventPlugin()
{
}

frts::ModulePtr frts::VanillaEventPlugin::getModule(frts::IdPtr id)
{
    assert(id != nullptr);

    frts::ModulePtr result = nullptr;
    if (id->toString() == EventManagerImpl::identifier())
    {
        result = makeEventManager();
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaEventPlugin)
