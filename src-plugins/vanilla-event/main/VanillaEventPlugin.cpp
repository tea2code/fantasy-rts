#include "VanillaEventPlugin.h"

#include <frts/shared>


frts::VanillaEventPlugin::VanillaEventPlugin()
{
}

frts::ModulePtr frts::VanillaEventPlugin::getModule(frts::IdPtr id)
{
    assert(id != nullptr);

    frts::ModulePtr result = nullptr;
//    if (id->toString() == CommandFactoryImpl::identifier())
//    {
//        result = makeCommandFactory();
//    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaEventPlugin)
