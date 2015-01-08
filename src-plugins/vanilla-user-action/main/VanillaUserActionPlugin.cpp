#include "VanillaUserActionPlugin.h"

#include "UserActionFactory.h"

#include <frts/shared>


frts::VanillaUserActionPlugin::VanillaUserActionPlugin()
{
}

frts::ModulePtr frts::VanillaUserActionPlugin::getModule(frts::IdPtr id)
{
    assert(id != nullptr);

    frts::ModulePtr result = nullptr;
    if (id->toString() == UserActionFactory::identifier())
    {
        result = makeUserActionFactory();
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaUserActionPlugin)
