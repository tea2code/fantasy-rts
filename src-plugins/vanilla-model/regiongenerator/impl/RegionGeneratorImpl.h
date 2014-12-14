#ifndef FRTS_REGIONGENERATORIMPL_H
#define FRTS_REGIONGENERATORIMPL_H

#include "OpenSimplexNoise.h"
#include <regiongenerator/RegionGenerator.h>

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

        WriteableBlockPtr newBlock(PointPtr pos, SharedManagerPtr shared);

    private:
        struct NoiseConfig
        {
            NoiseConfig(double featureSize, OpenSimplexNoise noise, std::vector<std::pair<double, double>> ranges, std::string id)
                : featureSize{featureSize}, noise{noise}, ranges{ranges}, id{id}
            {}
            double featureSize;
            OpenSimplexNoise noise;
            std::vector<std::pair<double, double>> ranges;
            std::string id;
        };

    private:
        IdPtr blockingType;
        IdPtr sortOrderType;

        Point::value surfaceZLevel = 0; // TODO Remove

        std::unordered_map<Point::value, std::vector<std::string>> levels;
        std::unordered_map<std::string, NoiseConfig> noises;
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
        return std::make_shared<RegionGeneratorImpl>(blockingType, sortOrderType);
    }
}

#endif // FRTS_REGIONGENERATORIMPL_H
