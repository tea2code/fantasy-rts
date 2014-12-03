#ifndef FRTS_REGIONCONFIGIMPL_H
#define FRTS_REGIONCONFIGIMPL_H

#include <main/ModelData.h>


namespace frts
{
    class ModelDataImpl : public ModelData
    {
    public:
        ModelDataImpl();

        std::string getName() const override;
        Point::value getMapSizeX() const override;
        Point::value getMapSizeY() const override;
        std::string getTypeName() const override;
        int getTypeVersion() const override;
        int getVersion() const override;
        void setMapSizeX(Point::value size) override;
        void setMapSizeY(Point::value size) override;

    private:
        Point::value sizeX;
        Point::value sizeY;
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

#endif // FRTS_REGIONCONFIGIMPL_H
