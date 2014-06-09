#include "VanillaModelPlugin.h"

#include "impl/ModelFactoryImpl.h"
#include "ModelReseter.h"

#include <frts/shared>

#include <memory>


frts::VanillaModelPlugin::VanillaModelPlugin()
{
}

frts::ModulePtr frts::VanillaModelPlugin::getModule(frts::IdPtr id)
{
    frts::ModulePtr result = nullptr;
    if (id->toString() == modelFactory)
    {
        result = makeModelFactory();
    }
    else if (id->toString() == modelReseter)
    {
        result = makeModelReseter();
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaModelPlugin)
