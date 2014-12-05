#ifndef FRTS_MAPPARSER_H
#define FRTS_MAPPARSER_H

#include <region/Point.h>
#include <region/WriteableBlock.h>

#include <frts/configuration>
#include <frts/shared>

#include <memory>


namespace frts
{
    class MapParser;

    /**
     * @brief Pointer to MapParser.
     */
    using MapParserPtr = std::shared_ptr<MapParser>;

    /**
     * @brief The map parser reads static map files and
     *        allows them to be used in region generators.
     */
    class MapParser
    {
    public:
        virtual ~MapParser() {}

        /**
         * @brief Get the block for given position if available.
         * @param pos The position.
         * @param shared The shared manager.
         * @return The generated block or null.
         */
        virtual WriteableBlockPtr newBlock(PointPtr pos, SharedManagerPtr shared) = 0;

        /**
         * @brief Parse the map parser config.
         * @param node The configuration node.
         * @param shared The shared manager.
         */
        virtual void parseConfig(ConfigNodePtr node, SharedManagerPtr shared) = 0;

        /**
         * @brief Validate the parsed config.
         * @throws DataViolation if a data value is invalid.
         * @param shared The shared manager.
         */
        virtual void validateData(SharedManagerPtr shared) = 0;
    };
}

#endif // FRTS_MAPPARSER_H