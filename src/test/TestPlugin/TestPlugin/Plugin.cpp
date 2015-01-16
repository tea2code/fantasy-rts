#include "Plugin.h"

#include "Tickable.h"
#include "Utility.h"

#include <frts/shared>

#include <memory>


const std::string Plugin::tickableId = "TestTickable";
const std::string Plugin::utilityId = "TestUtility";

Plugin::Plugin()
{

}

frts::ModulePtr Plugin::getModule(const frts::IdPtr& id)
{
    frts::ModulePtr result = nullptr;
    if (id->toString() == tickableId)
    {
        result = std::make_shared<Tickable>();
    }
    else if (id->toString() == utilityId)
    {
        result = std::make_shared<Utility>();
    }
    return result;
}

REGISTER_PLUGIN(Plugin)
