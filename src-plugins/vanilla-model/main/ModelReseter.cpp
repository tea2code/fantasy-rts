#include "ModelReseter.h"

#include "ModelFactory.h"
#include "ModelIds.h"
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

std::string frts::ModelReseter::getTypeName() const
{
    return getName();
}

int frts::ModelReseter::getTypeVersion() const
{
    return 1;
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
    auto regionManager = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    regionManager->resetChangedPos();
}

void frts::ModelReseter::validateData(SharedManagerPtr)
{
    // Cannot check here for RegionManager. See documentation "VanillaModel".
}

void frts::ModelReseter::validateModules(SharedManagerPtr shared)
{
    validateUtility(getName(), ModelIds::modelFactory(), 1, shared);
}
