#include "RegionGeneratorImpl.h"

#include <regiongenerator/RegionGeneratorIds.h>
#include <main/ModelIds.h>
#include <main/ModelFactory.h>
#include <region/impl/BlockImpl.h>
#include <frts/random.h>


frts::RegionGeneratorImpl::RegionGeneratorImpl(IdPtr blockingType, IdPtr sortOrderType)
    : blockingType{blockingType}, sortOrderType{sortOrderType}
{
}

frts::WriteableBlockPtr frts::RegionGeneratorImpl::newBlock(PointPtr pos, SharedManagerPtr shared)
{
    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    WriteableBlockPtr block = mf->getMapParser(shared->makeId(RegionGeneratorIds::bmpMapParser()))->newBlock(pos, shared);

    if (block == nullptr)
    {
        std::string idStr = "entity.grass";

        if (pos->getZ() < surfaceZLevel)
        {
            idStr = "entity.earth";
        }
        else if (pos->getZ() > surfaceZLevel)
        {
            idStr = "entity.air";
        }
        else if (randomFloat(0.0, 1.0) > 0.8)
        {
            idStr = "entity.wall";
        }

        block = makeBlock(blockingType, sortOrderType);
        block->insert(mf->makeEntity(shared->makeId(idStr), shared));
    }

    block->insert(mf->makeEntity(shared->makeId("entity.grid"), shared));

    return block;
}
