#include "VanillaJobPlugin.h"

#include <frts/shared>


frts::VanillaJobPlugin::VanillaJobPlugin()
{
}

frts::ModulePtr frts::VanillaJobPlugin::getModule(frts::IdPtr id)
{
    assert(id != nullptr);

    frts::ModulePtr result = nullptr;
//    if (id->toString() == EventManagerImpl::identifier())
//    {
//        result = makeEventManager();
//    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaJobPlugin)
