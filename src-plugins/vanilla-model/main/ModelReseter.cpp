#include "ModelReseter.h"

#include "RegionManager.h"

#include <boost/format.hpp>


frts::ModelReseter::ModelReseter()
{    
}

bool frts::ModelReseter::createData(SharedManagerPtr)
{
    return false;
}

std::string frts::ModelReseter::getName() const
{
    return "frts::ModelReseter";
}

std::vector<std::string> frts::ModelReseter::getSupportedConfig()
{
    return {};
}

int frts::ModelReseter::getVersion() const
{
    return 1;
}

bool frts::ModelReseter::init(SharedManagerPtr)
{
    return false;
}

void frts::ModelReseter::parseConfig(const std::string&, ConfigNodePtr, SharedManagerPtr)
{

}

bool frts::ModelReseter::preInit(SharedManagerPtr)
{
    return false;
}

void frts::ModelReseter::tick(SharedManagerPtr shared)
{
    IdPtr regionManagerId = shared->makeId(RegionManager::identifier());
    RegionManagerPtr regionManager = std::static_pointer_cast<RegionManager>(shared->getDataValue(regionManagerId));
    regionManager->resetChangedPos();
}

void frts::ModelReseter::validateData(SharedManagerPtr)
{
    // Cannot check here for RegionManager. See documentation "VanillaModel".
}

void frts::ModelReseter::validateModules(SharedManagerPtr shared)
{
    try
    {
        IdPtr id = shared->makeId("frts/ModelFactory");
        shared->getUtility(id);
    }
    catch(const IdNotFoundError&)
    {
        throw ModuleViolation("Utility ModelFactory not found.");
    }
}
