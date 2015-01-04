#include "VanillaActionPlugin.h"

#include <frts/shared>


frts::VanillaActionPlugin::VanillaActionPlugin()
{
}

frts::ModulePtr frts::VanillaActionPlugin::getModule(frts::IdPtr id)
{
    assert(id != nullptr);

    frts::ModulePtr result = nullptr;
//    if (id->toString() == EventManagerImpl::identifier())
//    {
//        result = makeEventManager();
//    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaActionPlugin)
