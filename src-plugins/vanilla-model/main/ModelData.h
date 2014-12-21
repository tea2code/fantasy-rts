#ifndef FRTS_MODELDATA_H
#define FRTS_MODELDATA_H

#include <region/Point.h>
#include <pathfinding/DistanceAlgorithm.h>

#include <frts/shared>

#include <memory>


namespace frts
{
    class ModelData;

    /**
     * @brief Pointer to ModelData.
     */
    using ModelDataPtr = std::shared_ptr<ModelData>;

    /**
     * @brief Stores settings of model.
     */
    class ModelData : public DataValue
    {
    public:
        virtual ~ModelData() {}

        /**
         * @brief Get map size in x direction.
         * @return The size.
         */
        virtual Point::value getMapSizeX() const = 0;

        /**
         * @brief Get map size in y direction.
         * @return The size.
         */
        virtual Point::value getMapSizeY() const = 0;

        /**
         * @brief Get number of z-levels to precalculate down.
         * @return Number of z-levels.
         */
        virtual unsigned int getPrecalculateDown() const = 0;

        /**
         * @brief Get number of z-levels to precalculate up.
         * @return Number of z-levels.
         */
        virtual unsigned int getPrecalculateUp() const = 0;

        /**
         * @brief Get the base z-level for the surface.
         * @return The z-level.
         */
        virtual Point::value getSurfaceZLevel() const = 0;

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

        /**
         * @brief Set number of z-levels to precalculate down.
         * @param zLevels Number of z-levels.
         */
        virtual void setPrecalculateDown(unsigned int zLevels) = 0;

        /**
         * @brief Set number of z-levels to precalculate up.
         * @param zLevels Number of z-levels.
         */
        virtual void setPrecalculateUp(unsigned int zLevels) = 0;

        /**
         * @brief Set the base z-level for the surface.
         * @param zLevel The z-level.
         */
        virtual void setSurfaceZLevel(Point::value zLevel) = 0;
    };
}

#endif // FRTS_MODELDATA_H
