#include "VanillaUserActionPlugin.h"

#include "impl/UserActionFactoryImpl.h"

#include <frts/shared>


frts::VanillaUserActionPlugin::VanillaUserActionPlugin()
{
}

frts::ModulePtr frts::VanillaUserActionPlugin::getModule(const IdPtr& id)
{
    assert(id != nullptr);

    frts::ModulePtr result = nullptr;
    if (id->toString() == UserActionFactoryImpl::identifier())
    {
        result = makeUserActionFactory();
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaUserActionPlugin)
