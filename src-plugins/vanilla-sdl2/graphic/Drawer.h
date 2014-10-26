#ifndef FRTS_DRAWER_H
#define FRTS_DRAWER_H

#include <frts/vanillamodel>

#include <vector>


namespace frts
{
    /**
     * @brief The drawer updates the screen and paints everything.
     */
    class Drawer
    {
    public:
        /**
         * @brief Update given position.
         * @param pos The position.
         */
        void updatePosition(PointPtr pos);

        /**
         * @brief Update all given positions.
         * @param positions List of positions.
         */
        void updatePositions(std::vector<PointPtr> positions);

        /**
         * @brief Update the whole screen.
         */
        void updateScreen();
    };
}

#endif // FRTS_DRAWER_H
