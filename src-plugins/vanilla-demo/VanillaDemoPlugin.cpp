#include "VanillaDemoPlugin.h"

#include "VanillaDemoTickable.h"

#include <frts/shared>

#include <memory>


frts::VanillaDemoPlugin::VanillaDemoPlugin()
{
}

frts::ModulePtr frts::VanillaDemoPlugin::getModule(frts::IdPtr id)
{
    assert(id != nullptr);

    frts::ModulePtr result = nullptr;
    if (id->toString() == VanillaDemoTickable::identifier())
    {
        result = std::make_shared<VanillaDemoTickable>();
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaDemoPlugin)
