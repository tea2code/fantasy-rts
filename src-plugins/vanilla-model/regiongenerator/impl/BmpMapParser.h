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
        BmpMapParser(const IdPtr& blockingType, const IdPtr& sortOrderType, const IdPtr& teleportType);

        std::string getSupportedConfig() const override;
        void init(const SharedManagerPtr& shared) override;
        WriteableBlockPtr newBlock(const PointPtr& pos, const SharedManagerPtr& shared) override;
        void parseConfig(const ConfigNodePtr& node, const SharedManagerPtr& shared) override;
        void validateData(const SharedManagerPtr& shared) override;

    private:
        struct RgbHash;

        /**
         * @brief Tuple of rgb color.
         */
        using Rgb = std::tuple<unsigned char, unsigned char, unsigned char>;

        /**
         * @brief Set of configured teleport colors.
         */
        using TeleportColors = std::unordered_set<Rgb, RgbHash>;

        /**
         * @brief Hash function for rgb values.
         */
        struct RgbHash
        {
            std::size_t operator() (const Rgb& rgb) const
            {
                return hasher(std::get<0>(rgb)) ^
                       hasher(std::get<1>(rgb)) ^
                       hasher(std::get<2>(rgb));
            }

        private:
            std::hash<unsigned char> hasher;
        };

    private:
        IdPtr blockingType;
        IdPtr sortOrderType;
        IdPtr teleportType;

        unsigned int height = 0;
        unsigned int width = 0;

        std::unordered_map<PointPtr, WriteableBlockPtr> blocks;
        std::unordered_map<Rgb, IdVector, RgbHash> colors;
        std::unordered_map<IdPtr, std::string> images;
        std::unordered_map<Point::value, IdPtr> levels;
        std::unordered_map<PointPtr, Rgb> mapPoints;
        Rgb neutralColor;

        TeleportColors teleportUp;
        TeleportColors teleportDown;

        std::unordered_map<Rgb, IdPtr, RgbHash> teleporters;
        std::unordered_map<IdPtr, PointVector> teleporterPoints;

    private:
        /**
         * @brief Connect two blocks if not already connected.
         * @param block The first block.
         * @param otherPos The position of the other block.
         * @param targets A list of already connected targets.
         * @param shared The shared manager.
         * @return The other teleport entity if a connection has happened.
         */
        EntityPtr connectIfNotYet(const WriteableBlockPtr& block, const PointPtr& otherPos,
                                  const EntityVector& targets, const SharedManagerPtr& shared);

        /**
         * @brief Get block at given position.
         * @param pos The position.
         * @param shared The shared manager.
         * @return The block.
         */
        WriteableBlockPtr getBlock(const PointPtr& pos, const SharedManagerPtr& shared);

        /**
         * @brief Parse the map image. Will store result in mapPoints.
         * @param path THe image path.
         * @param zLevel The z-level for given image file.
         * @param shared The shared manager.
         */
        void parseMap(const std::string& path, Point::value zLevel, const SharedManagerPtr& shared);

        /**
         * @brief Try to connect given block using teleport.
         * @param pos The position of this block.
         * @param block The block to connect.
         * @param teleportColorsBlock The teleport color which should be tried for this block.
         * @param teleportColorsOther The teleport color of the neightbors.
         * @param zLevelChange The change in z level to try.
         * @param shared The shared manager.
         */
        void tryConnectTeleport(const PointPtr& pos, const WriteableBlockPtr& block,
                                const TeleportColors& teleportColorsBlock,
                                const TeleportColors& teleportColorsOther, Point::value zLevelChange,
                                const SharedManagerPtr& shared);
    };

    /**
     * @brief Create new BmpMapParser.
     * @param blockingType The component type id of the blocking component.
     * @param sortOrderType The component type id of the sort order component.
     * @param teleportType The component type id of the teleport component.
     * @return The map parser.
     */
    inline MapParserPtr makeBmpMapParser(const IdPtr& blockingType, const IdPtr& sortOrderType, const IdPtr& teleportType)
    {
        assert(blockingType != nullptr);
        assert(sortOrderType != nullptr);
        assert(teleportType != nullptr);

        return std::make_shared<BmpMapParser>(blockingType, sortOrderType, teleportType);
    }
}

#endif // FRTS_BMPMAPPARSER_H
