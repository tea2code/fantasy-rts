#ifndef FRTS_REGIONCONFIGIMPL_H
#define FRTS_REGIONCONFIGIMPL_H

#include <main/RegionConfig.h>


namespace frts
{
    class RegionConfigImpl : public RegionConfig
    {
    public:
        RegionConfigImpl();

        std::string getName() const override;
        Point::value getMapSizeX() const override;
        Point::value getMapSizeY() const override;
        void setMapSizeX(Point::value size) override;
        void setMapSizeY(Point::value size) override;

    private:
        Point::value sizeX;
        Point::value sizeY;
    };

    /**
     * @brief Create new RegionConfig.
     * @return The RegionConfig.
     */
    inline RegionConfigPtr makeRegionConfig()
    {
        return std::make_shared<RegionConfigImpl>();
    }
}

#endif // FRTS_REGIONCONFIGIMPL_H
