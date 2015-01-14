#ifndef FRTS_REGIONGENERATORIMPL_H
#define FRTS_REGIONGENERATORIMPL_H

#include "OpenSimplexNoise.h"
#include <regiongenerator/RegionGenerator.h>
#include <main/ModelFactory.h>

#include <frts/shared>

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>


namespace frts
{
    class RegionGeneratorImpl : public RegionGenerator
    {
    public:
        /**
         * @param blockingType The component type id of the blocking component.
         * @param sortOrderType The component type id of the sort order component.
         */
        RegionGeneratorImpl(IdPtr blockingType, IdPtr sortOrderType);

        std::string getSupportedConfig() const override;
        void init(SharedManagerPtr shared) override;
        WriteableBlockPtr newBlock(PointPtr pos, SharedManagerPtr shared) override;
        void parseConfig(ConfigNodePtr node, SharedManagerPtr shared) override;
        void validateData(SharedManagerPtr shared) override;

    private:
        /**
         * @brief Simple struct containing all necessary data defining and generator.
         */
        struct Generator
        {
            Generator(double featureSize, OpenSimplexNoise noise, std::vector<std::pair<double, double>> ranges, IdVector entities)
                : featureSize{featureSize}, noise{noise}, ranges{ranges}, entities{entities}
            {}

            double featureSize;
            OpenSimplexNoise noise;
            std::vector<std::pair<double, double>> ranges;
            IdVector entities;
        };

    private:
        IdPtr blockingType;
        IdPtr sortOrderType;

        IdPtr defaultAboveSurfaceEntity;
        IdPtr defaultSurfaceEntity;
        IdPtr defaultBelowSurfaceEntity;

        IdVector defaultBelowSurfaceLevels;
        std::unordered_map<Point::value, IdVector> levels;
        std::unordered_map<IdPtr, Generator> generators;

    private:
        /**
         * @brief Initialize given block with generators.
         * @param block The block.
         * @param pos The position.
         * @param generatorIds List of generator IDs to use.
         * @param modelFactory The model factory.
         * @param shared The shared manager.
         * @return True if was initialized by generators.
         */
        bool initializeWithGenerators(WriteableBlockPtr block, PointPtr pos, const IdVector& generatorIds,
                                      ModelFactoryPtr modelFactory, SharedManagerPtr shared) const;
    };

    /**
     * @brief Create new region generator.
     * @param blockingType The component type id of the blocking component.
     * @param sortOrderType The component type id of the sort order component.
     * @param mapSizeX The map size in x direction.
     * @param mapSizeY The map size in y direction.
     * @return The region generator.
     */
    inline RegionGeneratorPtr makeRegionGenerator(IdPtr blockingType, IdPtr sortOrderType)
    {
        assert(blockingType != nullptr);
        assert(sortOrderType != nullptr);

        return std::make_shared<RegionGeneratorImpl>(blockingType, sortOrderType);
    }
}

#endif // FRTS_REGIONGENERATORIMPL_H
