#include "VanillaCommandPlugin.h"

#include "impl/CommandFactoryImpl.h"

#include <frts/shared>

#include <memory>


frts::VanillaCommandPlugin::VanillaCommandPlugin()
{
}

frts::ModulePtr frts::VanillaCommandPlugin::getModule(frts::IdPtr id)
{
    frts::ModulePtr result = nullptr;
    if (id->toString() == module)
    {
        result = makeCommandFactory();
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaCommandPlugin)