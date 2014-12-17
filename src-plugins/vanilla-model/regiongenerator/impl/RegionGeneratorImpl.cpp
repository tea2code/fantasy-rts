#include "RegionGeneratorImpl.h"

#include <regiongenerator/RegionGeneratorIds.h>
#include <main/ModelIds.h>
#include <main/ModelFactory.h>
#include <region/impl/BlockImpl.h>
#include <frts/random.h>

#include <boost/format.hpp>

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
{}

std::string frts::RegionGeneratorImpl::getSupportedConfig() const
{
    return "region_generator";
}

void frts::RegionGeneratorImpl::init(SharedManagerPtr)
{}

bool frts::RegionGeneratorImpl::initializeWithGenerators(WriteableBlockPtr block, PointPtr pos,
                                                         const IdVector& generatorIds,
                                                         ModelFactoryPtr modelFactory,
                                                         SharedManagerPtr shared) const
{
    bool initialized = false;
    for (auto& generatorId : generatorIds)
    {
        // This is save because we have already validated the existance of every generator in validateData().
        auto nc = generators.at(generatorId);

        double value = nc.noise.eval(static_cast<double>(pos->getX()) / nc.featureSize,
                                     static_cast<double>(pos->getY()) / nc.featureSize,
                                     static_cast<double>(pos->getZ()) / nc.featureSize);

        for (auto& range : nc.ranges)
        {
            if (range.first <= value && value <= range.second)
            {
                for (auto& id : nc.entities)
                {
                    block->insert(modelFactory->makeEntity(id, shared));
                    initialized = true;
                }
                break;
            }
        }
    }
    return initialized;
}

frts::WriteableBlockPtr frts::RegionGeneratorImpl::newBlock(PointPtr pos, SharedManagerPtr shared)
{
    auto mf = getUtility<ModelFactory>(shared, ModelIds::modelFactory());

    WriteableBlockPtr block = mf->getMapParser(shared->makeId(RegionGeneratorIds::bmpMapParser()))->newBlock(pos, shared);

    if (block == nullptr)
    {
        block = makeBlock(blockingType, sortOrderType);

        if (pos->getZ() < surfaceZLevel)
        {
            bool initializedWithGenerators = false;

            auto level = levels.find(pos->getZ());
            if (level != levels.end())
            {
                initializedWithGenerators = initializeWithGenerators(block, pos, level->second, mf, shared);
            }
            else if (!defaultBelowSurfaceLevels.empty())
            {
                initializedWithGenerators = initializeWithGenerators(block, pos, defaultBelowSurfaceLevels, mf, shared);
            }

            if (!initializedWithGenerators)
            {
                block->insert(mf->makeEntity(defaultBelowSurfaceEntity, shared));
            }
        }
        else if (pos->getZ() > surfaceZLevel)
        {
            block->insert(mf->makeEntity(defaultAboveSurfaceEntity, shared));
        }
        else
        {
            block->insert(mf->makeEntity(defaultSurfaceEntity, shared));
        }
    }

    //block->insert(mf->makeEntity(shared->makeId("entity.grid"), shared));

    return block;
}

void frts::RegionGeneratorImpl::parseConfig(ConfigNodePtr node, SharedManagerPtr shared)
{
    if (node->has("surface_level"))
    {
        surfaceZLevel = node->getInteger("surface_level");
    }

    if (node->has("default_above"))
    {
        defaultAboveSurfaceEntity = shared->makeId(node->getString("default_above"));
    }

    if (node->has("default_surface"))
    {
        defaultSurfaceEntity = shared->makeId(node->getString("default_surface"));
    }

    if (node->has("default_below"))
    {
        defaultBelowSurfaceEntity = shared->makeId(node->getString("default_below"));
    }

    // Noise map.
    if (!node->has("noise_map"))
    {
        return;
    }

    node = node->getNode("noise_map");

    std::string ns = node->getString("namespace", "");

    if (node->has("levels"))
    {
        ConfigNodePtr levelsNode = node->getNode("levels");

        if (levelsNode->has("default_below"))
        {
            for (auto& id : levelsNode->getStrings("default_below"))
            {
                defaultBelowSurfaceLevels.push_back(shared->makeId(id));
            }
        }

        if (levelsNode->has("levels"))
        {
            levelsNode = levelsNode->getNode("levels");
            for (ConfigNodePtr levelNode : *levelsNode)
            {
                int level = levelNode->getInteger("level");
                IdVector generators;
                for (auto& id : levelNode->getStrings("generators"))
                {
                    generators.push_back(shared->makeId(id));
                }
                levels[level] = generators;
            }
        }
    }

    if (node->has("generators"))
    {
        ConfigNodePtr generatorsNode = node->getNode("generators");

        if (generatorsNode->has("namespace"))
        {
            ns += "." + generatorsNode->getString("namespace");
        }

        if (generatorsNode->has("generators"))
        {
            generatorsNode = generatorsNode->getNode("generators");
            for (ConfigNodePtr generatorNode : *generatorsNode)
            {
                auto id = shared->makeId(ns + "." + generatorNode->getString("name"));
                double featureSize = generatorNode->getFloat("feature_size");

                std::vector<std::pair<double, double>> ranges;
                ConfigNodePtr rangesNode = generatorNode->getNode("ranges");
                for (ConfigNodePtr rangeNode : *rangesNode)
                {
                   ranges.emplace_back(rangeNode->getFloat("start"), rangeNode->getFloat("end"));
                }

                IdVector entities;
                for (auto& id : generatorNode->getStrings("entities"))
                {
                    entities.push_back(shared->makeId(id));
                }

                generators.emplace(id, Generator(featureSize, makeOpenSimplexNoise(), ranges, entities));
            }
        }
    }
}

void frts::RegionGeneratorImpl::validateData(SharedManagerPtr)
{
    if (defaultAboveSurfaceEntity == nullptr)
    {
        throw DataViolation("RegionGenerator: Config region_generator requires default_above.");
    }

    if (defaultBelowSurfaceEntity == nullptr)
    {
        throw DataViolation("RegionGenerator: Config region_generator requires default_below.");
    }

    if (defaultSurfaceEntity == nullptr)
    {
        throw DataViolation("RegionGenerator: Config region_generator requires default_surface.");
    }

    for (auto& id : defaultBelowSurfaceLevels)
    {
        if (generators.find(id) == generators.end())
        {
            auto msg = boost::format(R"(RegionGenerator: Generator "%1%" not found in config region_generator->noise_map->generators.)")
                    % id->toString();
            throw DataViolation(msg.str());
        }
    }

    for (auto& level : levels)
    {
        for (auto& id : level.second)
        {
            if (generators.find(id) == generators.end())
            {
                auto msg = boost::format(R"(RegionGenerator: Generator "%1%" not found in config region_generator->noise_map->generators.)")
                        % id->toString();
                throw DataViolation(msg.str());
            }
        }
    }
}
