#ifndef FRTS_DRAWER_H
#define FRTS_DRAWER_H

#include <graphic/impl/SpriteManager.h>

#include <frts/vanillamodel>

#include <SDL2/SDL.h>

#include <frts/shared>

#include <functional>
#include <memory>
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
         * @param shared The shared manager.
         */
        Drawer(SharedManagerPtr shared);
        ~Drawer();

        /**
         * @brief Set screen offset in x-direction. No boundary check.
         * @param offsetX The offset.
         */
        void setOffsetX(Point::value offsetX);

        /**
         * @brief Set screen offset in y-direction. No boundary check.
         * @param offsetY The offset.
         */
        void setOffsetY(Point::value offsetY);

        /**
         * @brief Update given position.
         * @param shared The shared manager.
         * @param pos The position.
         * @param zLevel The reference z-level.
         */
        void updatePosition(SharedManagerPtr shared, PointPtr pos, Point::value zLevel);

        /**
         * @brief Update all given positions.
         * @param shared The shared manager.
         * @param positions List of positions.
         * @param zLevel The reference z-level.
         */
        void updatePositions(SharedManagerPtr shared, std::vector<PointPtr> positions, Point::value zLevel);

        /**
         * @brief Update the whole screen.
         * @param shared The shared manager.
         * @param zLevel The z-level to show.
         */
        void updateScreen(SharedManagerPtr shared, Point::value zLevel);

    private:
        bool initialized;

        Point::value offsetX;
        Point::value offsetY;

        Point::value screenHeight;
        Point::value screenWidth;

        int tileHeight;
        int tileWidth;

        std::unique_ptr<SDL_Renderer> renderer;
        std::unique_ptr<SDL_Window> window;

        SpriteManager spriteManager;

    private:
        /**
         * @brief Retrieves the model factory.
         * @param shared The shared manager.
         * @return The model factory.
         */
        ModelFactoryPtr modelFactory(SharedManagerPtr shared) const;

        /**
         * @brief Retrieves the region manager.
         * @param shared The shared manager.
         * @return The region manager.
         */
        RegionManagerPtr regionManager(SharedManagerPtr shared) const;
    };
}

#endif // FRTS_DRAWER_H
