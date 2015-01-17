#ifndef FRTS_GRAPHICDATAIMPL_H
#define FRTS_GRAPHICDATAIMPL_H

#include <graphic/GraphicData.h>
#include <frts/BaseDataValue.h>

#include <string>
#include <memory>


namespace frts
{
    class GraphicDataImpl : public BaseDataValue<GraphicData>
    {
    public:
        GraphicDataImpl();

        EntityPtr getCursor() const override;
        ScreenArea getMapArea() const override;
        unsigned int getNumFpsAvg() const override;
        pixel getScreenHeight() const override;
        pixel getScreenOffsetStepX() const override;
        pixel getScreenOffsetStepY() const override;
        Point::value getScreenOffsetX() const override;
        Point::value getScreenOffsetY() const override;
        std::string getScreenTitle() const override;
        pixel getScreenWidth() const override;
        ScreenArea getSidebarArea() const override;
        int getSidebarInfoIndex() const override;
        pixel getSidebarWidth() const override;
        pixel getTileHeight() const override;
        pixel getTileWidth() const override;
        Point::value getZLevel() const override;
        double getZoom() const override;
        std::vector<double> getZoomLevels() const override;
        bool isRenderEverything() const override;
        void setCursor(const EntityPtr& cursor) override;
        void setMapArea(const ScreenArea& mapArea) override;
        void setNumFpsAvg(unsigned int numFpsAvg) override;
        void setRenderEverything(bool renderEverything = true) override;
        void setScreenHeight(pixel screenHeight) override;
        void setScreenOffsetStepX(pixel offsetStep) override;
        void setScreenOffsetStepY(pixel offsetStep) override;
        void setScreenOffsetX(Point::value offset) override;
        void setScreenOffsetY(Point::value offset) override;
        void setScreenTitle(const std::string& screenTitle) override;
        void setScreenWidth(pixel screenWidth) override;
        void setSidebarArea(const ScreenArea& sidebarArea) override;
        void setSidebarInfoIndex(int index) override;
        void setSidebarWidth(pixel sidebarWidth) override;
        void setTileHeight(pixel tileHeight) override;
        void setTileWidth(pixel tileWidth) override;
        void setZLevel(Point::value zLevel) override;
        void setZoom(double zoom) override;
        void setZoomLevels(std::vector<double> zoomLevels) override;

    private:
        EntityPtr cursor;
        ScreenArea mapArea;
        unsigned int maxFps = 0;
        unsigned int numFpsAvg = 0;
        bool renderEverything = false;
        pixel screenHeight = 0;
        pixel screenOffsetStepX = 0;
        pixel screenOffsetStepY = 0;
        Point::value screenOffsetX = 0;
        Point::value screenOffsetY = 0;
        std::string screenTitle;
        pixel screenWidth = 0;
        ScreenArea sidebarArea;
        int sidebarInfoIndex = sidebarInfoIndexDefault;
        pixel sidebarWidth = 0;
        pixel tileHeight = 0;
        pixel tileWidth = 0;
        Point::value zLevel = 0;
        double zoom = 1.0;
        std::vector<double> zoomLevels;
    };

    /**
     * @brief Create new GraphicData.
     * @return The GraphicData.
     */
    inline GraphicDataPtr makeGraphicData()
    {
        return std::make_shared<GraphicDataImpl>();
    }
}

#endif // FRTS_GRAPHICDATAIMPL_H
