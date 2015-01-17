#ifndef FRTS_GRAPHICDATA_H
#define FRTS_GRAPHICDATA_H

#include <frts/shared>
#include <frts/vanillamodel>

#include <memory>
#include <vector>
#include <string>


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
        /**
         * @brief Simple definition of a pixel value.
         */
        using pixel = unsigned int;

        /**
         * @brief The screen area describes an area in the window.
         */
        struct ScreenArea
        {
            ScreenArea(pixel x = 0, pixel y = 0, pixel width = 0, pixel height = 0)
                : x{x}, y{y}, width{width}, height{height}
            {}

            pixel x = 0;
            pixel y = 0;

            pixel width = 0;
            pixel height = 0;

            /**
             * @brief Checks if a pixel coordinate is inside the rectangle.
             * @param pixelX The x-component of the pixel coordinate.
             * @param pixelY The y-component of the pixel coordinate.
             * @return True if the pixel is inside the rectangle else false.
             */
            bool isPixelInRect(pixel pixelX, pixel pixelY)
            {
                return x <= pixelX && pixelX < x + width &&
                       y <= pixelY && pixelY < y + height;
            }
        };

    public:
        /**
         * @brief Default entity index for info area of sidebar.
         */
        const int sidebarInfoIndexDefault = -1;

    public:
        virtual ~GraphicData() {}

        /**
         * @return The cursor entity.
         */
        virtual EntityPtr getCursor() const = 0;

        /**
         * @return The map rectangle in the window.
         */
        virtual ScreenArea getMapArea() const = 0;
        /**
         * @return The number of fps measures for average calculation.
         */
        virtual unsigned int getNumFpsAvg() const = 0;

        /**
         * @return The screen height in pixel.
         */
        virtual pixel getScreenHeight() const = 0;

        /**
         * @return The screen offset step width in x direction in pixel.
         */
        virtual pixel getScreenOffsetStepX() const = 0;

        /**
         * @return The screen offset step width in y direction in pixel.
         */
        virtual pixel getScreenOffsetStepY() const = 0;

        /**
         * @return The current screen offset in x direction in number tiles.
         */
        virtual Point::value getScreenOffsetX() const = 0;

        /**
         * @return The current screen offset in y direction in number tiles.
         */
        virtual Point::value getScreenOffsetY() const = 0;

        /**
         * @return The screen title.
         */
        virtual std::string getScreenTitle() const = 0;

        /**
         * @return The screen width in pixel.
         */
        virtual pixel getScreenWidth() const = 0;

        /**
         * @return The sidebar rectangle in the window.
         */
        virtual ScreenArea getSidebarArea() const = 0;

        /**
         * @return Entity index for info area of sidebar.
         */
        virtual int getSidebarInfoIndex() const = 0;

        /**
         * @return The sidebar width in pixel.
         */
        virtual pixel getSidebarWidth() const = 0;

        /**
         * @return The tile height in pixel.
         */
        virtual pixel getTileHeight() const = 0;

        /**
         * @return The tile width in pixel.
         */
        virtual pixel getTileWidth() const = 0;

        /**
         * @return The current z-level.
         */
        virtual Point::value getZLevel() const = 0;

        /**
         * @return The current zoom multiplier.
         */
        virtual double getZoom() const = 0;

        /**
         * @return Ordered list of possible zoom levels.
         */
        virtual std::vector<double> getZoomLevels() const = 0;

        /**
         * @return Indicates if the renderer should rerender everything.
         */
        virtual bool isRenderEverything() const = 0;

        /**
         * @brief Set the cursor entity.
         * @param cursor The cursor.
         */
        virtual void setCursor(const EntityPtr& cursor) = 0;

        /**
         * @brief Set map rectangle in the window.
         * @param mapArea The map rectangle.
         */
        virtual void setMapArea(const ScreenArea& mapArea) = 0;

        /**
         * @brief Set the number of fps measures for average calculation.
         * @param maxFps The number of fps measures.
         */
        virtual void setNumFpsAvg(unsigned int numFpsAvg) = 0;

        /**
         * @brief Set if everything should be rerendered.
         * @param renderEverything Indicates if the renderer should rerender everything.
         */
        virtual void setRenderEverything(bool renderEverything = true) = 0;

        /**
         * @brief Set the screen height.
         * @param screenHeight The screen height.
         */
        virtual void setScreenHeight(pixel screenHeight) = 0;

        /**
         * @brief Set the screen offset step width in x direction.
         * @param offset The offset.
         */
        virtual void setScreenOffsetStepX(pixel offsetStep) = 0;

        /**
         * @brief Set the screen offset step width in y direction.
         * @param offset The offset.
         */
        virtual void setScreenOffsetStepY(pixel offsetStep) = 0;

        /**
         * @brief Set the current screen offset in x direction.
         * @param offset The offset.
         */
        virtual void setScreenOffsetX(Point::value offset) = 0;

        /**
         * @brief Set the current screen offset in y direction.
         * @param offset The offset.
         */
        virtual void setScreenOffsetY(Point::value offset) = 0;

        /**
         * @brief Set the screen title.
         * @param screenTitle The screen title.
         */
        virtual void setScreenTitle(const std::string& screenTitle) = 0;

        /**
         * @brief Set the screen width.
         * @param screenWidth The screen width.
         */
        virtual void setScreenWidth(pixel screenWidth) = 0;

        /**
         * @brief Set sidebar rectangle in the window.
         * @param mapArea The sidebar rectangle.
         */
        virtual void setSidebarArea(const ScreenArea& sidebarArea) = 0;

        /**
         * @brief Set entity index for info area of sidebar.
         * @param index The entity index.
         */
        virtual void setSidebarInfoIndex(int index) = 0;

        /**
         * @brief Set the sidebar width.
         * @param sidebarWidth The sidebar width.
         */
        virtual void setSidebarWidth(pixel sidebarWidth) = 0;

        /**
         * @brief Set the tile height.
         * @param tileHeight The tile height.
         */
        virtual void setTileHeight(pixel tileHeight) = 0;

        /**
         * @brief Set the tile width.
         * @param tileWidth The tile width.
         */
        virtual void setTileWidth(pixel tileWidth) = 0;

        /**
         * @brief Set the current z-level.
         * @param zLevel The z-level.
         */
        virtual void setZLevel(Point::value zLevel) = 0;

        /**
         * @brief Set current zoom level.
         * @param zoom The zoom level.
         */
        virtual void setZoom(double zoom) = 0;

        /**
         * @brief Set possible zoom levels.
         * @param zoomLevels The zoom levels.
         */
        virtual void setZoomLevels(std::vector<double> zoomLevels) = 0;
    };
}

#endif // FRTS_GRAPHICDATA_H
