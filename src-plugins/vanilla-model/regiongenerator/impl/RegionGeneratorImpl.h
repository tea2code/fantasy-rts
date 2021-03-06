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
        RegionGeneratorImpl();

        std::string getSupportedConfig() const override;
        void init(const SharedManagerPtr& shared) override;
        WriteableBlockPtr newBlock(const PointPtr& pos, const SharedManagerPtr& shared) override;
        void parseConfig(const ConfigNodePtr& node, const SharedManagerPtr& shared) override;
        void validateData(const SharedManagerPtr& shared) override;

    private:
        /**
         * @brief Simple struct containing all necessary data defining and generator.
         */
        struct Generator
        {
            Generator(double featureSize, const OpenSimplexNoise& noise,
                      const std::vector<std::pair<double, double>>& ranges, const IdVector& entities)
                : featureSize{featureSize}, noise{noise}, ranges{ranges}, entities{entities}
            {}

            double featureSize;
            OpenSimplexNoise noise;
            std::vector<std::pair<double, double>> ranges;
            IdVector entities;
        };

    private:
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
        bool initializeWithGenerators(const WriteableBlockPtr& block, const PointPtr& pos,
                                      const IdVector& generatorIds, const ModelFactoryPtr& modelFactory,
                                      const SharedManagerPtr& shared) const;
    };

    /**
     * @brief Create new region generator.
     * @return The region generator.
     */
    inline RegionGeneratorPtr makeRegionGenerator()
    {
        return std::make_shared<RegionGeneratorImpl>();
    }
}

#endif // FRTS_REGIONGENERATORIMPL_H
