#ifndef FRTS_GRAPHICDATAIMPL_H
#define FRTS_GRAPHICDATAIMPL_H

#include <graphic/GraphicData.h>

#include <string>
#include <memory>


namespace frts
{
    class GraphicDataImpl : public GraphicData
    {
    public:
        GraphicDataImpl();

        EntityPtr getCursor() const override;
        ScreenArea getMapArea() const override;
        unsigned int getMaxFps() const override;
        unsigned int getNumFpsAvg() const override;
        std::string getName() const override;
        Pixel getScreenHeight() const override;
        Pixel getScreenOffsetStepX() const override;
        Pixel getScreenOffsetStepY() const override;
        Point::value getScreenOffsetX() const override;
        Point::value getScreenOffsetY() const override;
        std::string getScreenTitle() const override;
        Pixel getScreenWidth() const override;
        ScreenArea getSidebarArea() const override;
        Pixel getSidebarWidth() const override;
        Pixel getTileHeight() const override;
        Pixel getTileWidth() const override;
        std::string getTypeName() const override;
        int getTypeVersion() const override;
        int getVersion() const override;
        Point::value getZLevel() const override;
        bool isRenderEverything() const override;
        void setCursor(EntityPtr cursor) override;
        void setMapArea(ScreenArea mapArea) override;
        void setMaxFps(unsigned int maxFps) override;
        void setNumFpsAvg(unsigned int numFpsAvg) override;
        void setRenderEverything(bool renderEverything = true) override;
        void setScreenHeight(Pixel screenHeight) override;
        void setScreenOffsetStepX(Pixel offsetStep) override;
        void setScreenOffsetStepY(Pixel offsetStep) override;
        void setScreenOffsetX(Point::value offset) override;
        void setScreenOffsetY(Point::value offset) override;
        void setScreenTitle(const std::string& screenTitle) override;
        void setScreenWidth(Pixel screenWidth) override;
        void setSidebarArea(ScreenArea sidebarArea) override;
        void setSidebarWidth(Pixel sidebarWidth) override;
        void setTileHeight(Pixel tileHeight) override;
        void setTileWidth(Pixel tileWidth) override;
        void setZLevel(Point::value zLevel) override;

    private:
        EntityPtr cursor;
        ScreenArea mapArea;
        unsigned int maxFps = 0;
        unsigned int numFpsAvg = 0;
        bool renderEverything = false;
        Pixel screenHeight = 0;
        Pixel screenOffsetStepX = 0;
        Pixel screenOffsetStepY = 0;
        Point::value screenOffsetX = 0;
        Point::value screenOffsetY = 0;
        std::string screenTitle;
        Pixel screenWidth = 0;
        ScreenArea sidebarArea;
        Pixel sidebarWidth = 0;
        Pixel tileHeight = 0;
        Pixel tileWidth = 0;
        Point::value zLevel = 0;
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
