#include "DemoRegionGenerator.h"

#include <region/impl/BlockImpl.h>
#include <frts/random.h>

#include <boost/format.hpp>


frts::DemoRegionGenerator::DemoRegionGenerator(IdPtr blockingType, IdPtr sortOrderType,
                                               Point::value mapSizeX, Point::value mapSizeY,
                                               Point::value surfaceZLevel)
    : blockingType{blockingType}, mapSizeX{mapSizeX}, mapSizeY{mapSizeY},
      sortOrderType{sortOrderType}, surfaceZLevel{surfaceZLevel}
{
}

std::map<frts::PointPtr, frts::WriteableBlockPtr> frts::DemoRegionGenerator::allBlocks(Point::value zLevel, SharedManagerPtr shared)
{
    auto msg = boost::format(R"(Generating map for z-level %1%.)") % zLevel;
    shared->getLog()->debug("frts::DemoRegionGenerator", msg.str());

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

    #ifdef A_STAR_BENCHMARK
    if (pos->getZ() == surfaceZLevel &&
        (pos->getX() + 1) % 10 == 0 &&
        10 < pos->getY() && pos->getY() < mapSizeY - 10)
    #else
    if (randomFloat(0.0, 1.0) > 0.8)
    #endif
    {
        idStr = "entity.wall";
    }
    else if (pos->getZ() < surfaceZLevel)
    {
        idStr = "entity.earth";
    }
    else if (pos->getZ() > surfaceZLevel)
    {
        idStr = "entity.air";
    }

    auto modelFactory = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    auto block = makeBlock(blockingType, sortOrderType);
    block->insert(modelFactory->makeEntity(shared->makeId(idStr), shared));
    block->insert(modelFactory->makeEntity(shared->makeId("entity.grid"), shared));
    return block;
}
