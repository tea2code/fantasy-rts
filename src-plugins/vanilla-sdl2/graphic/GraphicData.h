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
        /**
         * @brief Simple definition of a pixel value.
         */
        using Pixel = unsigned int;

        /**
         * @brief The screen rectangle describes a rectangle in the window.
         */
        struct ScreenArea
        {
            ScreenArea(Pixel x = 0, Pixel y = 0, Pixel width = 0, Pixel height = 0)
                : x{x}, y{y}, width{width}, height{height}
            {}

            Pixel x = 0;
            Pixel y = 0;

            Pixel width = 0;
            Pixel height = 0;

            /**
             * @brief Checks if a pixel coordinate is inside the rectangle.
             * @param pixelX The x-component of the pixel coordinate.
             * @param pixelY The y-component of the pixel coordinate.
             * @return True if the pixel is inside the rectangle else false.
             */
            bool isPixelInRect(Pixel pixelX, Pixel pixelY)
            {
                return x <= pixelX && pixelX <= x + width &&
                       y <= pixelY && pixelY <= y + height;
            }
        };

    public:
        virtual ~GraphicData() {}

        /**
         * @return The cursor entity.
         */
        virtual EntityPtr getCursor() const = 0;

        /**
         * @return The map rectangle in the window.
         */
        virtual ScreenArea getmapArea() const = 0;

        /**
         * @return The maximum frame rate.
         */
        virtual unsigned int getMaxFps() const = 0;

        /**
         * @return The number of fps measures for average calculation.
         */
        virtual unsigned int getNumFpsAvg() const = 0;

        /**
         * @return The screen height in pixel.
         */
        virtual Pixel getScreenHeight() const = 0;

        /**
         * @return The screen offset step width in x direction in pixel.
         */
        virtual Pixel getScreenOffsetStepX() const = 0;

        /**
         * @return The screen offset step width in y direction in pixel.
         */
        virtual Pixel getScreenOffsetStepY() const = 0;

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
        virtual Pixel getScreenWidth() const = 0;

        /**
         * @return The sidebar rectangle in the window.
         */
        virtual ScreenArea getsidebarArea() const = 0;

        /**
         * @return The sidebar width in pixel.
         */
        virtual Pixel getSidebarWidth() const = 0;

        /**
         * @return The tile height in pixel.
         */
        virtual Pixel getTileHeight() const = 0;

        /**
         * @return The tile width in pixel.
         */
        virtual Pixel getTileWidth() const = 0;

        /**
         * @return The current z-level.
         */
        virtual Point::value getZLevel() const = 0;

        /**
         * @return Indicates if the renderer should rerender everything.
         */
        virtual bool isRenderEverything() const = 0;

        /**
         * @brief Set the cursor entity.
         * @param cursor The cursor.
         */
        virtual void setCursor(EntityPtr cursor) = 0;

        /**
         * @brief Set map rectangle in the window.
         * @param mapArea The map rectangle.
         */
        virtual void setmapArea(ScreenArea mapArea) = 0;

        /**
         * @brief Set the maximum frame rate.
         * @param maxFps The maximum frame rate.
         */
        virtual void setMaxFps(unsigned int maxFps) = 0;

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
        virtual void setScreenHeight(Pixel screenHeight) = 0;

        /**
         * @brief Set the screen offset step width in x direction.
         * @param offset The offset.
         */
        virtual void setScreenOffsetStepX(Pixel offsetStep) = 0;

        /**
         * @brief Set the screen offset step width in y direction.
         * @param offset The offset.
         */
        virtual void setScreenOffsetStepY(Pixel offsetStep) = 0;

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
        virtual void setScreenWidth(Pixel screenWidth) = 0;

        /**
         * @brief Set sidebar rectangle in the window.
         * @param mapArea The sidebar rectangle.
         */
        virtual void setsidebarArea(ScreenArea sidebarArea) = 0;

        /**
         * @brief Set the sidebar width.
         * @param sidebarWidth The sidebar width.
         */
        virtual void setSidebarWidth(Pixel sidebarWidth) = 0;

        /**
         * @brief Set the tile height.
         * @param tileHeight The tile height.
         */
        virtual void setTileHeight(Pixel tileHeight) = 0;

        /**
         * @brief Set the tile width.
         * @param tileWidth The tile width.
         */
        virtual void setTileWidth(Pixel tileWidth) = 0;

        /**
         * @brief Set the current z-level.
         * @param zLevel The z-level.
         */
        virtual void setZLevel(Point::value zLevel) = 0;
    };
}

#endif // FRTS_GRAPHICDATA_H
