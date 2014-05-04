#include "VanillaDemoPlugin.h"

#include "VanillaDemoTickable.h"

#include <frts/shared>

#include <memory>


frts::VanillaDemoPlugin::VanillaDemoPlugin()
{
}

frts::ModulePtr frts::VanillaDemoPlugin::getModule(frts::IdPtr id)
{
    frts::ModulePtr result = nullptr;
    if (id->toString() == module)
    {
        result = std::make_shared<VanillaDemoTickable>();
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaDemoPlugin)
