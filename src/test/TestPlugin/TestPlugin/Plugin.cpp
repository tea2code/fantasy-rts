#include <plugin/PluginApi.h>

#include "Plugin.h"

#include "Module.h"

const std::string Plugin::moduleId = "TestModule";

Plugin::Plugin()
{

}

frts::ModulePtr Plugin::getModule(frts::IdPtr id)
{
    frts::ModulePtr result = nullptr;
    if (id->toString() == moduleId)
    {
        result = frts::ModulePtr(new Module());
    }
    return result;
}

REGISTER_PLUGIN(Plugin)