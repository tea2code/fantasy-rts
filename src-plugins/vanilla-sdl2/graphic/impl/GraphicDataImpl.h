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
        unsigned int getMaxFps() const override;
        std::string getName() const override;
        unsigned int getScreenHeight() const override;
        std::string getScreenTitle() const override;
        unsigned int getScreenWidth() const override;
        unsigned int getTileHeight() const override;
        unsigned int getTileWidth() const override;
        Point::value getZLevel() const override;
        bool isRenderEverything() const override;
        void setMaxFps(unsigned int maxFps) override;
        void setRenderEverything(bool renderEverything = true) override;
        void setScreenHeight(unsigned int screenHeight) override;
        void setScreenTitle(const std::string& screenTitle) override;
        void setScreenWidth(unsigned int screenWidth) override;
        void setTileHeight(unsigned int tileHeight) override;
        void setTileWidth(unsigned int tileWidth) override;
        void setZLevel(Point::value zLevel) override;

    private:
        unsigned int maxFps;
        bool renderEverything;
        int screenHeight;
        std::string screenTitle;
        int screenWidth;
        int tileHeight;
        int tileWidth;
        Point::value zLevel;
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
