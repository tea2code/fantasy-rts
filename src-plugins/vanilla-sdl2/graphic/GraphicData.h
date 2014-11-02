#ifndef FRTS_GRAPHICDATA_H
#define FRTS_GRAPHICDATA_H

#include <frts/shared>
#include <frts/vanillamodel>

#include <string>
#include <memory>


namespace frts
{
    class GraphicData;

    /**
     * @brief Pointer to GraphicData.
     */
    using GraphicDataPtr = std::shared_ptr<GraphicData>;

    /**
     * @brief This data value stores some data related graphics.
     */
    class GraphicData : public DataValue
    {
    public:
        virtual ~GraphicData() {}

        /**
         * @return The screen height in pixel.
         */
        virtual int getScreenHeight() const;

        /**
         * @return The screen title.
         */
        virtual std::string getScreenTitle() const;

        /**
         * @return The screen width in pixel.
         */
        virtual int getScreenWidth() const;

        /**
         * @return The tile height in pixel.
         */
        virtual int getTileHeight() const;

        /**
         * @return The tile width in pixel.
         */
        virtual int getTileWidth() const;

        /**
         * @return The current z-level.
         */
        virtual Point::value getZLevel() const;

        /**
         * @brief Set the screen height.
         * @param screenHeight The screen height.
         */
        virtual void setScreenHeight(int screenHeight);

        /**
         * @brief Set the screen title.
         * @param screenTitle The screen title.
         */
        virtual void setScreenTitle(const std::string& screenTitle);

        /**
         * @brief Set the screen width.
         * @param screenWidth The screen width.
         */
        virtual void setScreenWidth(int screenWidth);

        /**
         * @brief Set the tile height.
         * @param tileHeight The tile height.
         */
        virtual void setTileHeight(int tileHeight);

        /**
         * @brief Set the tile width.
         * @param tileWidth The tile width.
         */
        virtual void setTileWidth(int tileWidth);

        /**
         * @brief Set the current z-level.
         * @param zLevel The z-level.
         */
        virtual void setZLevel(Point::value zLevel);
    };
}

#endif // FRTS_GRAPHICDATA_H
