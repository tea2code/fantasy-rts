#include "ModelReseter.h"

#include "ModelFactory.h"
#include "ModelIds.h"
#include "RegionManager.h"


frts::ModelReseter::ModelReseter()
    : BaseTickable("frts::ModelReseter", 1, "frts::ModelReseter", 1)
{    
}

void frts::ModelReseter::tick(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto regionManager = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    regionManager->resetChangedPos();
}

void frts::ModelReseter::validateModules(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateUtility(getName(), ModelIds::modelFactory(), 1, shared);
}
