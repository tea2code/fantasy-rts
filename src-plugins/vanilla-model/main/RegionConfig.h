#ifndef FRTS_REGIONCONFIG_H
#define FRTS_REGIONCONFIG_H

#include <region/Point.h>

#include <frts/shared>

#include <memory>


namespace frts
{
    class RegionConfig;

    /**
     * @brief Pointer to RegionConfig.
     */
    using RegionConfigPtr = std::shared_ptr<RegionConfig>;

    /**
     * @brief Stores settings of region.
     */
    class RegionConfig : public DataValue
    {
    public:
        virtual ~RegionConfig() {}

        /**
         * @brief Get map size in x direction.
         * @return The size.
         */
        virtual Point::value getMapSizeX() const = 0;

        /**
         * @brief Get map size in y direction.
         * @return  The size.
         */
        virtual Point::value getMapSizeY() const = 0;

        /**
         * @brief Set map size in x direction.
         * @param size The size.
         */
        virtual void setMapSizeX(Point::value size) = 0;

        /**
         * @brief Set map size in y direction.
         * @param size The size.
         */
        virtual void setMapSizeY(Point::value size) = 0;
    };
}

#endif // FRTS_REGIONCONFIG_H
