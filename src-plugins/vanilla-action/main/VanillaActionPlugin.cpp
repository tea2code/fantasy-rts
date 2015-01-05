#include "VanillaActionPlugin.h"

#include "impl/ActionManagerImpl.h"


frts::VanillaActionPlugin::VanillaActionPlugin()
{
}

frts::ModulePtr frts::VanillaActionPlugin::getModule(frts::IdPtr id)
{
    assert(id != nullptr);

    frts::ModulePtr result = nullptr;
    if (id->toString() == ActionManagerImpl::identifier())
    {
        result = makeActionManager();
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaActionPlugin)
