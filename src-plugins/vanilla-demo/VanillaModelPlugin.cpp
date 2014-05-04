#include "VanillaModelPlugin.h"

#include "VanillaDemoTickable.h"

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
        result = std::make_shared<VanillaDemoTickable>();
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaModelPlugin)
