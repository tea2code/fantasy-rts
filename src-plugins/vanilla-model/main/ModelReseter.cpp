#include "ModelReseter.h"

#include "ModelFactory.h"
#include "ModelIds.h"
#include "RegionManager.h"

#include <boost/format.hpp>


frts::ModelReseter::ModelReseter()
    : BaseTickable("frts::ModelReseter", 1, "frts::ModelReseter", 1)
{    
}

void frts::ModelReseter::tick(SharedManagerPtr shared)
{
    auto regionManager = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    regionManager->resetChangedPos();
}

void frts::ModelReseter::validateModules(SharedManagerPtr shared)
{
    validateUtility(getName(), ModelIds::modelFactory(), 1, shared);
}
