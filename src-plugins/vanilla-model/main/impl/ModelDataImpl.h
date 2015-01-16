#ifndef FRTS_MODELDATAIMPL_H
#define FRTS_MODELDATAIMPL_H

#include <main/ModelData.h>
#include <frts/BaseDataValue.h>


namespace frts
{
    class ModelDataImpl : public BaseDataValue<ModelData>
    {
    public:
        ModelDataImpl();

        Point::value getMapSizeX() const override;
        Point::value getMapSizeY() const override;
        unsigned int getPrecalculateDown() const override;
        unsigned int getPrecalculateUp() const override;
        ZLevelRange getPrecalculatedRange() const override;
        Point::value getSurfaceZLevel() const override;
        void setMapSizeX(Point::value size) override;
        void setMapSizeY(Point::value size) override;
        void setPrecalculateDown(unsigned int zLevels) override;
        void setPrecalculateUp(unsigned int zLevels) override;
        void setPrecalculatedRange(ZLevelRange range) override;
        void setSurfaceZLevel(Point::value zLevel) override;

    private:
        unsigned int precalculateDown = 0;
        unsigned int precalculateUp = 0;
        ZLevelRange precalculatedRange;
        Point::value sizeX = 0;
        Point::value sizeY = 0;
        Point::value surfaceZLevel = 0;
    };

    /**
     * @brief Create new ModelData.
     * @return The RegionConfig.
     */
    inline ModelDataPtr makeModelData()
    {
        return std::make_shared<ModelDataImpl>();
    }
}

#endif // FRTS_MODELDATAIMPL_H
