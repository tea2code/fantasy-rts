#include "ModelReseter.h"

#include "ModelFactory.h"
#include "ModelIds.h"
#include "RegionManager.h"


frts::ModelReseter::ModelReseter()
    : BaseTickable("frts::ModelReseter", 1, "frts::ModelReseter", 1)
{    
}

void frts::ModelReseter::tick(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    auto regionManager = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    regionManager->resetChangedPos();
}

void frts::ModelReseter::validateModules(const SharedManagerPtr& shared)
{
    assert(shared != nullptr);

    validateUtility(getName(), ModelIds::modelFactory(), 2, shared);
}
