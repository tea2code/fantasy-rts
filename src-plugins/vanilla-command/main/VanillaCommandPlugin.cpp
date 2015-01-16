#include "VanillaCommandPlugin.h"

#include "impl/CommandFactoryImpl.h"

#include <frts/shared>


frts::VanillaCommandPlugin::VanillaCommandPlugin()
{
}

frts::ModulePtr frts::VanillaCommandPlugin::getModule(const IdPtr& id)
{
    assert(id != nullptr);

    frts::ModulePtr result = nullptr;
    if (id->toString() == CommandFactoryImpl::identifier())
    {
        result = makeCommandFactory();
    }
    return result;
}

REGISTER_PLUGIN(frts::VanillaCommandPlugin)
