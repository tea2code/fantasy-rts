#ifndef FRTS_GRAPHICUTILITY_H
#define FRTS_GRAPHICUTILITY_H

#include <graphic/GraphicData.h>
#include <frts/shared>
#include <frts/vanillamodel>


namespace frts
{
    /**
     * @brief Raise an move cursor event with the new cursor position.
     * @param cursorPos The new cursor position.
     * @param shared The shared manager.
     */
    void raiseMoveCursorEvent(const PointPtr& cursorPos, const SharedManagerPtr& shared);

    /**
     * @brief Calculates how many tiles are equivalent to the the given number of pixel in x direction.
     * @param pixel The number of pixel.
     * @param shared The shared manager.
     * @return The number of tiles.
     */
    Point::value pixelToTilesX(GraphicData::pixel pixel, const SharedManagerPtr& shared);

   /** @brief Calculates how many tiles are equivalent to the the given number of pixel in y direction.
    * @param pixel The number of pixel.
    * @param shared The shared manager.
    * @return The number of tiles.
    */
   Point::value pixelToTilesY(GraphicData::pixel pixel, const SharedManagerPtr& shared);

    /**
     * @brief Calculates how many pixel are equivalent to the the given number of tiles in x direction.
     * @param tiles The number of tiles.
     * @param shared The shared manager.
     * @return The number of pixel.
     */
    GraphicData::pixel tilesToPixelX(Point::value tiles, const SharedManagerPtr& shared);

    /**
     * @brief Calculates how many pixel are equivalent to the the given number of tiles in y direction.
     * @param tiles The number of tiles.
     * @param shared The shared manager.
     * @return The number of pixel.
     */
    GraphicData::pixel tilesToPixelY(Point::value tiles, const SharedManagerPtr& shared);
}

#endif // FRTS_GRAPHICUTILITY_H
