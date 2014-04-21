#include "Plugin.h"

#include "Module.h"

#include <frts/shared>


const std::string Plugin::moduleId = "TestModule";

Plugin::Plugin()
{

}

frts::ModulePtr Plugin::getModule(frts::IdPtr id) noexcept
{
    frts::ModulePtr result = nullptr;
    if (id->toString() == moduleId)
    {
        result = frts::ModulePtr(new Module());
    }
    return result;
}

REGISTER_PLUGIN(Plugin)
