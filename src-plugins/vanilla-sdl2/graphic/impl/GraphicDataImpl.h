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
        unsigned int getMaxFps() const override;
        unsigned int getNumFpsAvg() const override;
        std::string getName() const override;
        unsigned int getScreenHeight() const override;
        unsigned int getScreenOffsetStepX() const override;
        unsigned int getScreenOffsetStepY() const override;
        Point::value getScreenOffsetX() const override;
        Point::value getScreenOffsetY() const override;
        std::string getScreenTitle() const override;
        unsigned int getScreenWidth() const override;
        unsigned int getTileHeight() const override;
        unsigned int getTileWidth() const override;
        std::string getTypeName() const override;
        int getTypeVersion() const override;
        int getVersion() const override;
        Point::value getZLevel() const override;
        bool isRenderEverything() const override;
        void setCursor(EntityPtr cursor) override;
        void setMaxFps(unsigned int maxFps) override;
        void setNumFpsAvg(unsigned int numFpsAvg) override;
        void setRenderEverything(bool renderEverything = true) override;
        void setScreenHeight(unsigned int screenHeight) override;
        void setScreenOffsetStepX(unsigned int offsetStep) override;
        void setScreenOffsetStepY(unsigned int offsetStep) override;
        void setScreenOffsetX(Point::value offset) override;
        void setScreenOffsetY(Point::value offset) override;
        void setScreenTitle(const std::string& screenTitle) override;
        void setScreenWidth(unsigned int screenWidth) override;
        void setTileHeight(unsigned int tileHeight) override;
        void setTileWidth(unsigned int tileWidth) override;
        void setZLevel(Point::value zLevel) override;

    private:
        EntityPtr cursor;
        unsigned int maxFps = 0;
        unsigned int numFpsAvg = 0;
        bool renderEverything = false;
        unsigned int screenHeight = 0;
        unsigned int screenOffsetStepX = 0;
        unsigned int screenOffsetStepY = 0;
        Point::value screenOffsetX = 0;
        Point::value screenOffsetY = 0;
        std::string screenTitle;
        unsigned int screenWidth = 0;
        unsigned int tileHeight = 0;
        unsigned int tileWidth = 0;
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
