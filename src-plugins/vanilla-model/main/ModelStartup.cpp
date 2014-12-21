#include "ModelStartup.h"

#include "ModelData.h"
#include "ModelFactory.h"
#include "ModelIds.h"
#include "RegionManager.h"


frts::ModelStartup::ModelStartup()
    : BaseTickable("frts::ModelStartup", 1, "frts::ModelStartup", 1)
{

}

void frts::ModelStartup::checkRequiredData(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateDataValue(getName(), ModelIds::modelData(), 2, shared);
}

void frts::ModelStartup::tick(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    auto regionManager = getDataValue<RegionManager>(shared, ModelIds::regionManager());
    auto modelData = getDataValue<ModelData>(shared, ModelIds::modelData());
    auto modelFactory = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    // Precalculate levels.
    shared->getLog()->info(getName(), "Precalculating z-levels. This will take some time.");
    Point::value zMin = static_cast<Point::value>(modelData->getSurfaceZLevel() - modelData->getPrecalculateDown());
    Point::value zMax = static_cast<Point::value>(modelData->getSurfaceZLevel() + modelData->getPrecalculateUp());
    for (Point::value x = 0; x < modelData->getMapSizeX(); ++x)
    {
        for (Point::value y = 0; y < modelData->getMapSizeY(); ++y)
        {
            for (Point::value z = zMin; z <= zMax; ++z)
            {
                auto pos = modelFactory->makePoint(x, y, z);
                regionManager->getBlock(pos, shared);
            }
        }
    }
    regionManager->resetChangedPos();
    shared->getLog()->info(getName(), "Precalculation complete.");
}

void frts::ModelStartup::validateModules(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    validateUtility(getName(), ModelIds::modelFactory(), 1, shared);
}