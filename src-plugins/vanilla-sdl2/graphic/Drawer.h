#ifndef FRTS_DRAWER_H
#define FRTS_DRAWER_H

#include <frts/vanillamodel>

#include <memory>
#include <vector>


namespace frts
{
    class Drawer;

    /**
     * @brief Pointer to Drawer.
     */
    using DrawerPtr = std::shared_ptr<Drawer>;

    /**
     * @brief A drawer updates the screen and paints everything.
     */
    class Drawer
    {
    public:
        virtual ~Drawer() {}

        /**
         * @brief Update given position.
         * @param pos The position.
         */
        virtual void updatePosition(Point pos) = 0;

        /**
         * @brief Update all given positions.
         * @param positions List of positions.
         */
        virtual void updatePositions(std::vector<Point> positions) = 0;

        /**
         * @brief Update the whole screen.
         */
        virtual void updateScreen() = 0;
    };
}

#endif // FRTS_DRAWER_H
