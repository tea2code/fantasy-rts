#include "VanillaModelPlugin.h"

#include "ModelIds.h"
#include "ModelReseter.h"
#include "impl/ModelFactoryImpl.h"

#include <frts/shared>

#include <memory>


frts::VanillaModelPlugin::VanillaModelPlugin()
{
}

frts::ModulePtr frts::VanillaModelPlugin::getModule(frts::IdPtr id)
{
    frts::ModulePtr result = nullptr;
    if (id->toString() == ModelIds::modelFactory())
    {
        result = makeModelFactory();
    }
    else if (id->toString() == ModelReseter::identifier())
    {
        result = makeModelReseter();
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaModelPlugin)
