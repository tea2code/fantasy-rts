#include "VanillaModelPlugin.h"

#include <frts/shared>

#include <memory>


frts::VanillaModelPlugin::VanillaModelPlugin()
{
}

frts::ModulePtr frts::VanillaModelPlugin::getModule(frts::IdPtr id)
{
    frts::ModulePtr result = nullptr;
    if (id->toString() == module)
    {
        // TODO
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaModelPlugin)
