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
        virtual unsigned int getScreenHeight() const = 0;

        /**
         * @return The screen title.
         */
        virtual std::string getScreenTitle() const = 0;

        /**
         * @return The screen width in pixel.
         */
        virtual unsigned int getScreenWidth() const = 0;

        /**
         * @return The tile height in pixel.
         */
        virtual unsigned int getTileHeight() const = 0;

        /**
         * @return The tile width in pixel.
         */
        virtual unsigned int getTileWidth() const = 0;

        /**
         * @return The current z-level.
         */
        virtual Point::value getZLevel() const = 0;

        /**
         * @return Indicates if the renderer should rerender everything.
         */
        virtual bool isRenderEverything() const = 0;

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
        virtual void setScreenHeight(unsigned int screenHeight) = 0;

        /**
         * @brief Set the screen title.
         * @param screenTitle The screen title.
         */
        virtual void setScreenTitle(const std::string& screenTitle) = 0;

        /**
         * @brief Set the screen width.
         * @param screenWidth The screen width.
         */
        virtual void setScreenWidth(unsigned int screenWidth) = 0;

        /**
         * @brief Set the tile height.
         * @param tileHeight The tile height.
         */
        virtual void setTileHeight(unsigned int tileHeight) = 0;

        /**
         * @brief Set the tile width.
         * @param tileWidth The tile width.
         */
        virtual void setTileWidth(unsigned int tileWidth) = 0;

        /**
         * @brief Set the current z-level.
         * @param zLevel The z-level.
         */
        virtual void setZLevel(Point::value zLevel) = 0;
    };
}

#endif // FRTS_GRAPHICDATA_H
