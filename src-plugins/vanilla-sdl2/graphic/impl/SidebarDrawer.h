#ifndef FRTS_SIDEBARDRAWER_H
#define FRTS_SIDEBARDRAWER_H

#include "Drawer.h"
#include <graphic/GraphicData.h>
#include <frts/configuration>
#include <frts/shared>

#include <SDL2/SDL.h>

#include <cstdint>
#include <vector>


namespace frts
{
    /**
     * @brief Helper class which draws the sidebar. Executing the rendering must happen somewhere else.
     */
    class SidebarDrawer
    {
    public:
        SidebarDrawer();
        ~SidebarDrawer();

        /**
         * @brief Initialize drawer. Any configuration must be set before.
         * @param renderer The renderer.
         * @param shared The shared manager.
         */
        void init(Drawer::RendererPtr renderer, SharedManagerPtr shared);

        /**
         * @brief Set the sidebar configuration.
         * @param shared The shared manager.
         * @param sidebarNode The sidebar config node.
         */
        void setSidebarConfig(SharedManagerPtr shared, ConfigNodePtr sidebarNode);

        /**
         * @brief Update events in sidebar.
         * @param events List of events to render.
         * @param shared The shared manager.
         */
        void updateEvents(std::vector<IdPtr> events, SharedManagerPtr shared);

        /**
         * @brief Update tile info in sidebar.
         * @param shared The shared manager.
         */
        void updateInfo(SharedManagerPtr shared);

        /**
         * @brief Update complete sidebar.
         * @param events List of events to render.
         * @param shared The shared manager.
         */
        void updateSidebar(std::vector<IdPtr> events, SharedManagerPtr shared);

        /**
         * @brief Validate configuration. Should be called during data validation phase.
         * @param shared The shared manager.
         */
        void validateData(SharedManagerPtr shared);

    private:
        bool initialized = false;
        Drawer::RendererPtr renderer;

        std::uint8_t backgroundR = 0;
        std::uint8_t backgroundG = 0;
        std::uint8_t backgroundB = 0;

        SDL_Color fontColor;

        std::uint8_t lineColorR = 0;
        std::uint8_t lineColorG = 0;
        std::uint8_t lineColorB = 0;

        std::uint8_t tileBackgroundR = 0;
        std::uint8_t tileBackgroundG = 0;
        std::uint8_t tileBackgroundB = 0;

    private:
        /**
         * @brief Draw an rectangle.
         * @param x The x coordinate.
         * @param y The y coordinate.
         * @param width The width.
         * @param height The height.
         * @param r RGB component red.
         * @param g RGB component green.
         * @param b RGB component blue.
         */
        void drawRectangle(GraphicData::Pixel x, GraphicData::Pixel y, GraphicData::Pixel width, GraphicData::Pixel height,
                           std::uint8_t r, std::uint8_t g, std::uint8_t b);
    };
}

#endif // FRTS_SIDEBARDRAWER_H
