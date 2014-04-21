#include "Plugin.h"

#include "Tickable.h"
#include "Utility.h"

#include <frts/shared>


const std::string Plugin::tickableId = "TestTickable";
const std::string Plugin::utilityId = "TestUtility";

Plugin::Plugin()
{

}

frts::ModulePtr Plugin::getModule(frts::IdPtr id) noexcept
{
    frts::ModulePtr result = nullptr;
    if (id->toString() == tickableId)
    {
        result = frts::TickablePtr(new Tickable());
    }
    else if (id->toString() == utilityId)
    {
        result = frts::UtilityPtr(new Utility());
    }
    return result;
}

REGISTER_PLUGIN(Plugin)
