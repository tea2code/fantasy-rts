#ifndef FRTS_BMPMAPPARSER_H
#define FRTS_BMPMAPPARSER_H

#include <regiongenerator/MapParser.h>

#include <tuple>
#include <unordered_map>
#include <vector>


namespace frts
{
    class BmpMapParser : public MapParser
    {
    public:
        /**
         * @param blockingType The component type id of the blocking component.
         * @param sortOrderType The component type id of the sort order component.
         */
        BmpMapParser(IdPtr blockingType, IdPtr sortOrderType);

        std::string getSupportedConfig() override;
        void init(SharedManagerPtr shared) override;
        WriteableBlockPtr newBlock(PointPtr pos, SharedManagerPtr shared) override;
        void parseConfig(ConfigNodePtr node, SharedManagerPtr shared) override;
        void validateData(SharedManagerPtr shared) override;

    private:
        struct RgbHash;

        /**
         * @brief Tuple of rgb color.
         */
        using Rgb = std::tuple<int, int, int>;

        /**
         * @brief Set of configured teleport colors.
         */
        using TeleportColors = std::unordered_set<Rgb, RgbHash>;

        /**
         * @brief Map of targets for teleports.
         */
        using TeleportPointsMap = std::unordered_map<PointPtr, std::unordered_set<PointPtr, PointHash, PointEqual>, PointHash, PointEqual>;

        /**
         * @brief Hash function for rgb values.
         */
        struct RgbHash
        {
            std::size_t operator() (Rgb rgb) const
            {
                return intHash(std::get<0>(rgb)) ^
                       intHash(std::get<1>(rgb)) ^
                       intHash(std::get<2>(rgb));
            }

        private:
            std::hash<int> intHash;
        };

    private:
        IdPtr blockingType;
        IdPtr sortOrderType;

        unsigned int height = 0;
        unsigned int width = 0;

        std::unordered_map<Rgb, std::vector<IdPtr>, RgbHash> colors;
        std::unordered_map<IdPtr, std::string, IdHash, IdEqual> images;
        std::unordered_map<Point::value, IdPtr> levels;
        std::unordered_map<PointPtr, Rgb, PointHash, PointEqual> mapPoints;
        Rgb neutralColor;

        TeleportColors teleportUp;
        TeleportColors teleportDown;
        TeleportPointsMap teleportUpPositions;
        TeleportPointsMap teleportDownPositions;

    private:
        /**
         * @brief Parse the map image. Will store result in mapPoints.
         * @param path THe image path.
         * @param zLevel The z-level for given image file.
         * @param shared The shared manager.
         */
        void parseMap(const std::string& path, Point::value zLevel, SharedManagerPtr shared);
    };

    /**
     * @brief Create new BmpMapParser.
     * @param blockingType The component type id of the blocking component.
     * @param sortOrderType The component type id of the sort order component.
     * @return The map parser.
     */
    inline MapParserPtr makeBmpMapParser(IdPtr blockingType, IdPtr sortOrderType)
    {
        return std::make_shared<BmpMapParser>(blockingType, sortOrderType);
    }
}

#endif // FRTS_BMPMAPPARSER_H
