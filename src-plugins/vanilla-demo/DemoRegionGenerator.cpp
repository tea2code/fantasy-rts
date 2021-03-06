#include "DemoRegionGenerator.h"

#include <region/impl/BlockImpl.h>
#include <frts/random.h>


frts::DemoRegionGenerator::DemoRegionGenerator(const IdPtr& blockingType, const IdPtr& sortOrderType,
                                               Point::value mapSizeX, Point::value mapSizeY,
                                               Point::value surfaceZLevel)
    : blockingType{blockingType}, mapSizeX{mapSizeX}, mapSizeY{mapSizeY},
      sortOrderType{sortOrderType}, surfaceZLevel{surfaceZLevel}
{
}

std::string frts::DemoRegionGenerator::getSupportedConfig() const
{
    return "";
}

void frts::DemoRegionGenerator::init(const SharedManagerPtr&)
{}

frts::WriteableBlockPtr frts::DemoRegionGenerator::newBlock(const PointPtr& pos, const SharedManagerPtr& shared)
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

    auto block = modelFactory->makeBlock(shared);
    block->insert(modelFactory->makeEntity(shared->makeId(idStr), shared));
    block->insert(modelFactory->makeEntity(shared->makeId("entity.grid"), shared));
    return block;
}

void frts::DemoRegionGenerator::parseConfig(const ConfigNodePtr&, const SharedManagerPtr&)
{}

void frts::DemoRegionGenerator::validateData(const SharedManagerPtr&)
{}
