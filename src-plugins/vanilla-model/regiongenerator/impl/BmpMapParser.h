#ifndef FRTS_BMPMAPPARSER_H
#define FRTS_BMPMAPPARSER_H

#include <entity/Teleport.h>
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
         * @param teleportType The component type id of the teleport component.
         */
        BmpMapParser(IdPtr blockingType, IdPtr sortOrderType, IdPtr teleportType);

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
        IdPtr teleportType;

        unsigned int height = 0;
        unsigned int width = 0;

        std::unordered_map<PointPtr, WriteableBlockPtr, PointHash, PointEqual> blocks;
        std::unordered_map<Rgb, std::vector<IdPtr>, RgbHash> colors;
        std::unordered_map<IdPtr, std::string, IdHash, IdEqual> images;
        std::unordered_map<Point::value, IdPtr> levels;
        std::unordered_map<PointPtr, Rgb, PointHash, PointEqual> mapPoints;
        Rgb neutralColor;

        TeleportColors teleportUp;
        TeleportColors teleportDown;

    private:
        /**
         * @brief Get block at given position.
         * @param pos The position.
         * @param shared The shared manager.
         * @return The block.
         */
        WriteableBlockPtr getBlock(PointPtr pos, SharedManagerPtr shared);

        /**
         * @brief Parse the map image. Will store result in mapPoints.
         * @param path THe image path.
         * @param zLevel The z-level for given image file.
         * @param shared The shared manager.
         */
        void parseMap(const std::string& path, Point::value zLevel, SharedManagerPtr shared);

        /**
         * @brief Try to connect given block using teleport.
         * @param pos The position of this block.
         * @param block The block to connect.
         * @param teleportColorsBlock The teleport color which should be tried for this block.
         * @param teleportColorsOther The teleport color of the neightbors.
         * @param zLevelChange The change in z level to try.
         * @param shared The shared manager.
         */
        void tryConnectTeleport(PointPtr pos, WriteableBlockPtr block, const TeleportColors& teleportColorsBlock,
                                const TeleportColors& teleportColorsOther, Point::value zLevelChange, SharedManagerPtr shared);
    };

    /**
     * @brief Create new BmpMapParser.
     * @param blockingType The component type id of the blocking component.
     * @param sortOrderType The component type id of the sort order component.
     * @param teleportType The component type id of the teleport component.
     * @return The map parser.
     */
    inline MapParserPtr makeBmpMapParser(IdPtr blockingType, IdPtr sortOrderType, IdPtr teleportType)
    {
        return std::make_shared<BmpMapParser>(blockingType, sortOrderType, teleportType);
    }
}

#endif // FRTS_BMPMAPPARSER_H
