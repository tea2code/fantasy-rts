#ifndef FRTS_GRAPHICUTILITY_H
#define FRTS_GRAPHICUTILITY_H

#include <graphic/GraphicData.h>

#include <frts/vanillamodel>


namespace frts
{
    /**
     * @brief Converts screen coordinates in pixel to region coordinates in tiles.
     * @param screen The screen coordinate (x or y).
     * @param tile The tile width or height.
     * @return The region coordinate (x or y).
     */
    Point::value screenToRegion(GraphicData::pixel screen, int tile);

    /**
     * @brief Converts region coordinates in tiles to screen coordinates in pixel.
     * @param region The region coordinate (x or y).
     * @param tile The tile width or height.
     * @return The screen coordinate (x or y).
     */
    GraphicData::pixel regionToScreen(Point::value region, int tile);
}

#endif // FRTS_GRAPHICUTILITY_H
