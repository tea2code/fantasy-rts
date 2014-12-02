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
         * @brief Get default distance algorithm.
         * @return The distance algorithm.
         */
        virtual DistanceAlgorithmPtr getDistanceAlgorithm() const = 0;

        /**
         * @brief Get default hase resource type.
         * @return The resource type.
         */
        virtual IdPtr getHasResourceType() const = 0;

        /**
         * @brief Get default is resource type.
         * @return The resource type.
         */
        virtual IdPtr getIsResourceType() const = 0;

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
         * @brief Set default distance algorithm. Can be used for example for
         *        resource managers and path finder. Should be initialized
         *        before phase 10.
         * @param distanceAlgorithm The distance algorithm.
         */
        virtual void setDistanceAlgorithm(DistanceAlgorithmPtr distanceAlgorithm) = 0;

        /**
         * @brief Set default has resource type. Can be used for example for
         *        resource managers and path finder. Should be initialized
         *        before phase 10.
         * @param hasResourceType The resource type.
         */
        virtual void setHasResourceType(IdPtr hasResourceType) = 0;

        /**
         * @brief Set default is resource type. Can be used for example for
         *        resource managers and path finder. Should be initialized
         *        before phase 10.
         * @param isResourceType The resource type.
         */
        virtual void setIsResourceType(IdPtr isResourceType) = 0;

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

#endif // FRTS_MODELDATA_H
