#ifndef FRTS_REGIONGENERATOR_H
#define FRTS_REGIONGENERATOR_H

#include <region/Point.h>
#include <region/WriteableBlock.h>
#include <frts/configuration>

#include <map>
#include <memory>


namespace frts
{
    class RegionGenerator;

    /**
     * @brief Pointer to RegionGenerator.
     */
    using RegionGeneratorPtr = std::shared_ptr<RegionGenerator>;

    /**
     * @brief A region generator creates all the blocks in a certain
     *        region.
     */
    class RegionGenerator
    {
    public:
        virtual ~RegionGenerator() {}

        /**
         * @brief Get the supported config key.
         * @return The key.
         */
        virtual std::string getSupportedConfig() const = 0;

        /**
         * @brief Initialize the map parser.
         * @param shared The shared manager.
         */
        virtual void init(const SharedManagerPtr& shared) = 0;

        /**
         * @brief Get a new point for given position.
         * @param pos The position.
         * @param shared The shared manager.
         * @return The generated block.
         */
        virtual WriteableBlockPtr newBlock(const PointPtr& pos, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Parse the map parser config.
         * @param node The configuration node.
         * @param shared The shared manager.
         */
        virtual void parseConfig(const ConfigNodePtr& node, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Validate the parsed config.
         * @throws DataViolation if a data value is invalid.
         * @param shared The shared manager.
         */
        virtual void validateData(const SharedManagerPtr& shared) = 0;
    };
}

#endif // FRTS_REGIONGENERATOR_H
