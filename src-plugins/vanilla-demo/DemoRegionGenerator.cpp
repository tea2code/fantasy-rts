#include "DemoRegionGenerator.h"

#include <frts/vanillamodel>
#include <region/impl/BlockImpl.h>


frts::DemoRegionGenerator::DemoRegionGenerator(IdPtr blockingType, IdPtr sortOrderType,
                                               Point::value mapSizeX, Point::value mapSizeY,
                                               Point::value surfaceZLevel)
    : blockingType{blockingType}, mapSizeX{mapSizeX}, mapSizeY{mapSizeY}, sortOrderType{sortOrderType},
      surfaceZLevel{surfaceZLevel}
{
}

std::map<frts::PointPtr, frts::WriteableBlockPtr> frts::DemoRegionGenerator::allBlocks(Point::value zLevel, SharedManagerPtr shared)
{
    auto modelFactory = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    std::map<PointPtr, WriteableBlockPtr> result;
    for (Point::value x = 0; x < mapSizeX; ++x)
    {
        for (Point::value y = 0; y < mapSizeY; ++y)
        {
            auto pos = modelFactory->makePoint(x, y, zLevel);
            result[pos] = newBlock(pos, shared);
        }
    }
    return result;
}

frts::WriteableBlockPtr frts::DemoRegionGenerator::newBlock(PointPtr pos, SharedManagerPtr shared)
{
    std::string idStr = "entity.grass";
    if (pos->getZ() < surfaceZLevel)
    {
        idStr = "entity.dirt";
    }
    else if (pos->getZ() > surfaceZLevel)
    {
        idStr = "entity.air";
    }

    auto modelFactory = getUtility<ModelFactory>(shared, ModelIds::modelFactory());
    auto id = shared->makeId(idStr);
    auto entity = modelFactory->makeEntity(id, shared);

    auto block = makeBlock(blockingType, sortOrderType);
    block->insert(entity);
    return block;
}
