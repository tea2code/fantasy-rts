#include "RegionGeneratorImpl.h"

#include <regiongenerator/RegionGeneratorIds.h>
#include <main/ModelIds.h>
#include <main/ModelFactory.h>
#include <region/impl/BlockImpl.h>
#include <frts/random.h>

#include <cmath>
#include <limits>


frts::RegionGeneratorImpl::RegionGeneratorImpl(IdPtr blockingType, IdPtr sortOrderType)
    : blockingType{blockingType}, sortOrderType{sortOrderType},
      noise{randomInteger(std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max())}
{
}

frts::WriteableBlockPtr frts::RegionGeneratorImpl::newBlock(PointPtr pos, SharedManagerPtr shared)
{
    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    WriteableBlockPtr block = mf->getMapParser(shared->makeId(RegionGeneratorIds::bmpMapParser()))->newBlock(pos, shared);

    if (block == nullptr)
    {
        std::string id = "entity.grass";

        if (pos->getZ() < surfaceZLevel)
        {
            double featureSize = 10;
//            if (pos->getZ() <= -3)
//            {
//                featureSize = 10;
//            }
//            else if (pos->getZ() <= -4)
//            {
//                featureSize = 5;
//            }

            double value = noise.eval(static_cast<double>(pos->getX()) / featureSize,
                                      static_cast<double>(pos->getY()) / featureSize,
                                      static_cast<double>(pos->getZ()) / featureSize);

            // This will create a nearly uniform distribution by sliding the negativ values over the positives.
//            if (value < 0.0)
//            {
//                value += 1.0;
//            }
//            long lookup = std::lround(value * 1000.0);
            long lookup = std::lround((value + 1.0) * 500.0);

            id = "entity.earth";
            if ((pos->getZ() == -1 && lookup >= 800) ||
                (pos->getZ() <= -2 && lookup >= 500) ||
                (pos->getZ() == -3 && lookup >= 200) ||
                (pos->getZ() <= -4))
            {
                if (pos->getZ() < -3 && 750 <= lookup && lookup <= 850)
                {
                    id = "entity.rock.iron";
                }
                else if (pos->getZ() < -2 && 150 <= lookup && lookup <= 250)
                {
                    id = "entity.rock.coal";
                }
                else if (pos->getZ() < -4 && 450 <= lookup && lookup <= 460)
                {
                    id = "entity.rock.diamond";
                }
                else
                {
                    id = "entity.rock";
                }
            }
        }
        else if (pos->getZ() > surfaceZLevel)
        {
            id = "entity.air";
        }

        block = makeBlock(blockingType, sortOrderType);
        block->insert(mf->makeEntity(shared->makeId(id), shared));
    }

    //block->insert(mf->makeEntity(shared->makeId("entity.grid"), shared));

    return block;
}
