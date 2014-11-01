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
        std::string getName() const override;
        int getScreenHeight() const override;
        std::string getScreenTitle() const override;
        int getScreenWidth() const override;
        int getTileHeight() const override;
        int getTileWidth() const override;
        void setScreenHeight(int screenHeight) override;
        void setScreenTitle(const std::string& screenTitle) override;
        void setScreenWidth(int screenWidth) override;
        void setTileHeight(int tileHeight) override;
        void setTileWidth(int tileWidth) override;

    private:
        int screenHeight;
        std::string screenTitle;
        int screenWidth;
        int tileHeight;
        int tileWidth;
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
