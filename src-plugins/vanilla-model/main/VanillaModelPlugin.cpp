#include "VanillaModelPlugin.h"

#include "impl/ModelFactoryImpl.h"

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
        result = std::make_shared<ModelFactoryImpl>();
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaModelPlugin)
