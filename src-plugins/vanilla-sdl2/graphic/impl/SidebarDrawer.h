#ifndef FRTS_SIDEBARDRAWER_H
#define FRTS_SIDEBARDRAWER_H

#include "Drawer.h"
#include <graphic/GraphicData.h>
#include <frts/configuration>
#include <frts/shared>
#include <frts/vanillaevent>
#include <frts/vanillamodel>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <cstdint>
#include <list>
#include <memory>
#include <vector>
#include <unordered_map>


namespace frts
{
    class SidebarDrawer;

    /**
     * @brief Pointer to SidebarDrawer.
     */
    using SidebarDrawerPtr = std::shared_ptr<SidebarDrawer>;

    /**
     * @brief Helper class which draws the sidebar. Executing the rendering must happen somewhere else.
     */
    class SidebarDrawer : public EventObserver
    {
    public:
        SidebarDrawer();
        ~SidebarDrawer();

        void notify(EventPtr event, SharedManagerPtr shared) override;

        /**
         * @brief Get class name.
         * @return The name.
         */
        std::string getName() const;

        /**
         * @brief Don't call before init() was called.
         * @return A list of event types the sidebar drawer must be observer of.
         */
        IdVector getSidebarEvents() const;

        /**
         * @brief Initialize drawer. Any configuration must be set before.
         * @param drawer The drawer.
         * @param shared The shared manager.
         */
        void init(DrawerPtr drawer, SharedManagerPtr shared);

        /**
         * @brief Set the sidebar configuration.
         * @param shared The shared manager.
         * @param sidebarNode The sidebar config node.
         */
        void setSidebarConfig(SharedManagerPtr shared, ConfigNodePtr sidebarNode);

        /**
         * @brief Update events in sidebar.
         * @param shared The shared manager.
         * @param forceUpdate If set to true an update will be executed even if it seems not necessary.
         * @return True if something has been updated else false.
         */
        bool updateEvents(SharedManagerPtr shared, bool forceUpdate = false);

        /**
         * @brief Update tile info in sidebar.
         * @param shared The shared manager.
         * @param forceUpdate If set to true an update will be executed even if it seems not necessary.
         * @return True if something has been updated else false.
         */
        bool updateInfo(SharedManagerPtr shared, bool forceUpdate = false);

        /**
         * @brief Update complete sidebar.
         * @param shared The shared manager.
         * @return True if something has been updated else false.
         */
        bool updateSidebar(SharedManagerPtr shared);

        /**
         * @brief Validate configuration. Should be called during data validation phase.
         * @param shared The shared manager.
         */
        void validateData(SharedManagerPtr shared);

    private:
        struct EventSubscription
        {
            IdVector eventValues;
            std::string text;
        };

        /**
         * @brief Map of event subscriptions.
         */
        using EventSubscriptionMap = std::unordered_map<IdPtr, EventSubscription>;

        /**
         * @brief Pointer to SDL font.
         */
        using FontPtr = std::unique_ptr<TTF_Font, Drawer::Sdl2Deleter>;

    private:
        bool initialized = false;

        std::uint8_t backgroundR = 0;
        std::uint8_t backgroundG = 0;
        std::uint8_t backgroundB = 0;

        DrawerPtr drawer;

        std::list<EventPtr> events;

        GraphicData::pixel eventsHeight = 0;

        EventSubscriptionMap eventSubscriptions;

        bool eventsChanged = true;
        Frame::time eventsNextUpdate;
        Frame::time eventsUpdateTime;

        Drawer::TexturePtr eventTexture;

        GraphicData::pixel eventOffset = 0;

        IdPtr eventValueBool;
        IdPtr eventValueFloat;
        IdPtr eventValueInteger;
        IdPtr eventValueId;
        IdPtr eventValueString;
        IdPtr eventValuePoint;
        IdPtr eventValueEntity;

        std::string fontPath;
        int fontSize = 0;
        FontPtr font;
        SDL_Color fontColor;

        unsigned int infoLastCountEntities = 0;
        EntityPtr infoLastEntity;
        int infoLastEntityIndex;
        PointPtr infoLastPos;

        Frame::time infoNextUpdate;
        Frame::time infoUpdateTime;

        GraphicData::pixel infoOffset = 0;

        bool infoOnlyWithComponent = true;

        std::string infoText;
        GraphicData::pixel infoTextHeight = 0;

        Drawer::TexturePtr infoTexture;

        std::uint8_t lineColorR = 0;
        std::uint8_t lineColorG = 0;
        std::uint8_t lineColorB = 0;

        GraphicData::pixel padding = 0;

        std::uint8_t tileBackgroundR = 0;
        std::uint8_t tileBackgroundG = 0;
        std::uint8_t tileBackgroundB = 0;

        unsigned int tileZoom = 1;

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
        void drawRectangle(GraphicData::pixel x, GraphicData::pixel y, GraphicData::pixel width, GraphicData::pixel height,
                           std::uint8_t r, std::uint8_t g, std::uint8_t b);

        /**
         * @brief Draw a separation line.
         * @param startX The x coordinate of the start.
         * @param endX The x coordinate of the end.
         * @param y The y coordinate
         */
        void drawSeparationLine(GraphicData::pixel startX, GraphicData::pixel endX, GraphicData::pixel y);

        /**
         * @brief Render given text.
         * @param text The text to render.
         * @param x The x coordinate.
         * @param y The y coordinate.
         * @param maxWidth The max width of the text before a line break.
         * @param maxHeight The max height of the text.
         * @param shared The shared manager.
         * @return The rendered texture or null if failed.
         */
        Drawer::TexturePtr drawText(const std::string& text, GraphicData::pixel x, GraphicData::pixel y,
                                    GraphicData::pixel maxWidth, GraphicData::pixel maxHeight, SharedManagerPtr shared);
    };

    /**
     * @brief Create new sidebar drawer.
     * @return The sidebar drawer.
     */
    inline SidebarDrawerPtr makeSidebarDrawer()
    {
        return std::make_shared<SidebarDrawer>();
    }
}

#endif // FRTS_SIDEBARDRAWER_H
