#include "RegionGeneratorImpl.h"

#include <regiongenerator/RegionGeneratorIds.h>
#include <main/ModelIds.h>
#include <main/ModelFactory.h>
#include <region/impl/BlockImpl.h>
#include <frts/random.h>

#include <cmath>
#include <limits>


namespace {
    frts::OpenSimplexNoise makeOpenSimplexNoise()
    {
        return frts::OpenSimplexNoise(frts::randomInteger(std::numeric_limits<long long>::min(), std::numeric_limits<long long>::max()));
    }
}

frts::RegionGeneratorImpl::RegionGeneratorImpl(IdPtr blockingType, IdPtr sortOrderType)
    : blockingType{blockingType}, sortOrderType{sortOrderType}
{
    levels.emplace(-1, std::vector<std::string>{"frts.vanillamodel.noise.rock.1"});
    levels.emplace(-2, std::vector<std::string>{"frts.vanillamodel.noise.rock.2"});
    levels.emplace(-3, std::vector<std::string>{"frts.vanillamodel.noise.rock.3", "frts.vanillamodel.noise.coal"});
    levels.emplace(-4, std::vector<std::string>{"frts.vanillamodel.noise.rock.3", "frts.vanillamodel.noise.coal", "frts.vanillamodel.noise.iron", "frts.vanillamodel.noise.diamond"});

    noises.emplace("frts.vanillamodel.noise.coal", NoiseConfig(15.0, makeOpenSimplexNoise(), {{-1.0, -0.5}, {0.5, 1.0}}, "entity.rock.coal"));
    noises.emplace("frts.vanillamodel.noise.iron", NoiseConfig(10.0, makeOpenSimplexNoise(), {{-1.0, -0.6}, {0.6, 1.0}}, "entity.rock.iron"));
    noises.emplace("frts.vanillamodel.noise.diamond", NoiseConfig(3.0, makeOpenSimplexNoise(), {{-1.0, -0.8}, {0.8, 1.0}}, "entity.rock.diamond"));
    noises.emplace("frts.vanillamodel.noise.rock.1", NoiseConfig(30.0, makeOpenSimplexNoise(), {{-1.0, -0.8}, {0.8, 1.0}}, "entity.rock"));
    noises.emplace("frts.vanillamodel.noise.rock.2", NoiseConfig(30.0, makeOpenSimplexNoise(), {{-1.0, -0.4}, {0.4, 1.0}}, "entity.rock"));
    noises.emplace("frts.vanillamodel.noise.rock.3", NoiseConfig(30.0, makeOpenSimplexNoise(), {{-1.0, 1.0}}, "entity.rock"));
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
            id = "entity.earth";
            for (auto& noise : levels.at(pos->getZ()))
            {
                auto nc = noises.at(noise);

                double value = nc.noise.eval(static_cast<double>(pos->getX()) / nc.featureSize,
                                             static_cast<double>(pos->getY()) / nc.featureSize,
                                             static_cast<double>(pos->getZ()) / nc.featureSize);

                for (auto& range : nc.ranges)
                {
                    if (range.first <= value && value <= range.second)
                    {
                        id = nc.id;
                        break;
                    }
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
