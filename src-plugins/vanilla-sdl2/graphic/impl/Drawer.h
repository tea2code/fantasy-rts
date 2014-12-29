#ifndef FRTS_DRAWER_H
#define FRTS_DRAWER_H

#include <graphic/GraphicData.h>
#include <graphic/impl/SpriteManager.h>
#include <frts/shared>
#include <frts/vanillamodel>

#include <SDL2/SDL.h>

#include <cstdint>
#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>


namespace frts
{
    /**
     * @brief Thrown if the image config is invalid.
     */
    class InvalidImageConfigError : public DataViolation
    {
    public:
        InvalidImageConfigError(const std::string& msg) : DataViolation(msg) {}
    };

    /**
     * @brief The drawer updates the screen and paints everything.
     */
    class Drawer
    {
    public:
        /**
         * @brief Deleter for smart pointer for SDL2.
         * @see http://stackoverflow.com/a/24252225
         */
        struct Sdl2Deleter
        {
          void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
          void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
          void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
        };

    public:
        /**
         * @brief Pointer to SDL renderer.
         */
        using RendererPtr = std::shared_ptr<SDL_Renderer>;

    public:
        Drawer();
        ~Drawer();

        /**
         * @brief Get the renderer. Only call after init().
         * @return The renderer.
         */
        RendererPtr getRenderer() const;

        /**
         * @brief Initialize drawer. Any configuration must be set before.
         * @param shared The shared manager.
         */
        void init(SharedManagerPtr shared);

        /**
         * @brief After updating positions call this function to start the rendering.
         * @param shared The shared manager.
         */
        void renderNow(SharedManagerPtr shared);

        /**
         * @brief Set background color for filling of map tiles.
         * @param r The red part of rgb.
         * @param g The green part of rgb.
         * @param b The blue part of rgb.
         */
        void setTileBackground(std::uint8_t r = 0, std::uint8_t g = 0, std::uint8_t b = 0);

        /**
         * @brief Set configuration for image. Can be called multiple times to override
         *        existing config or add images.
         * @throw InvalidImageConfigError if image node represents a invalid config.
         * @param shared The shared manager.
         * @param rootNamespace The root namespace of images.
         * @param imagesNode The config node.
         */
        void setImageConfig(SharedManagerPtr shared, const std::string& rootNamespace, ConfigNodePtr imagesNode);

        /**
         * @brief Set tile offset in x-direction. No boundary check.
         * @param offsetX The offset.
         */
        void setOffsetX(Point::value offsetX);

        /**
         * @brief Set tile offset in y-direction. No boundary check.
         * @param offsetY The offset.
         */
        void setOffsetY(Point::value offsetY);

        /**
         * @brief Set configuration for sprites. Can be called multiple times to override
         *        existing config or add sprites.
         * @throw InvalidSpriteConfigError if sprite node represents a invalid config.
         * @param shared The shared manager.
         * @param rootNamespace The root namespace of sprites.
         * @param spritesNode The config node.
         */
        void setSpriteConfig(SharedManagerPtr shared, const std::string& rootNamespace, ConfigNodePtr spritesNode);

        /**
         * @brief Set the window title.
         * @param windowTitle The window title.
         */
        void setWindowTitle(const std::string& windowTitle);

        /**
         * @brief Update the whole map area.
         * @param shared The shared manager.
         * @param zLevel The z-level to show.
         * @param regionManager The region manager.
         * @param modelFactory The model factory.
         * @param graphicData The graphic data.
         */
        void updateMap(SharedManagerPtr shared, Point::value zLevel,
                          RegionManagerPtr regionManager, ModelFactoryPtr modelFactory, GraphicDataPtr graphicData);

        /**
         * @brief Update given position.
         * @param shared The shared manager.
         * @param pos The position.
         * @param zLevel The reference z-level.
         * @param regionManager The region manager.
         * @param modelFactory The model factory.
         * @param graphicData The graphic data.
         */
        void updatePosition(SharedManagerPtr shared, PointPtr pos, Point::value zLevel,
                            RegionManagerPtr regionManager, ModelFactoryPtr modelFactory, GraphicDataPtr graphicData);

        /**
         * @brief Update all given positions.
         * @param shared The shared manager.
         * @param positions List of positions.
         * @param zLevel The reference z-level.
         * @param regionManager The region manager.
         * @param modelFactory The model factory.
         * @param graphicData The graphic data.
         */
        void updatePositions(SharedManagerPtr shared, const PointUnorderedSet& positions, Point::value zLevel,
                             RegionManagerPtr regionManager, ModelFactoryPtr modelFactory, GraphicDataPtr graphicData);

        /**
         * @brief Validate configuration. Should be called during data validation phase.
         * @throw InvalidSpriteConfigError if sprite node represents a invalid config.
         * @throw InvalidImageConfigError if image node represents a invalid config.
         * @param shared The shared manager.
         */
        void validateData(SharedManagerPtr shared);

    private:
        /**
         * @brief Pointer to SDL texture.
         */
        using TexturePtr = std::shared_ptr<SDL_Texture>;

        /**
         * @brief Pointer to SDL window.
         */
        using WindowPtr = std::unique_ptr<SDL_Window, Sdl2Deleter>;

        /**
         * @brief Lookup map for textures.
         */
        using TextureMap = std::unordered_map<IdPtr, TexturePtr, IdHash, IdEqual>;

        /**
         * @brief Lookup map for image paths.
         */
        using ImageMap = std::unordered_map<IdPtr, std::string, IdHash, IdEqual>;

    private:
        bool initialized = false;

        /**
         * @brief Offset in number of tiles in x-direction.
         */
        Point::value offsetX = 0;

        /**
         * @brief Offset in number of tiles in y-direction.
         */
        Point::value offsetY = 0;

        /**
         * @brief Screen height in number tiles.
         */
        Point::value screenHeight = 0;

        /**
         * @brief Screen width in number tiles.
         */
        Point::value screenWidth = 0;

        /**
         * @brief Map width in number tiles.
         */
        Point::value mapWidth = 0;

        /**
         * @brief Sidebar width in number tiles.
         */
        Point::value sidebarWidth = 0;

        int tileHeight = 0;
        int tileWidth = 0;

        RendererPtr renderer;
        TextureMap textures;
        WindowPtr window;

        ImageMap images;
        SpriteManager spriteManager;

        std::uint8_t tileBackgroundR = 0;
        std::uint8_t tileBackgroundG = 0;
        std::uint8_t tileBackgroundB = 0;

    private:
        /**
         * @brief Returns name of class for usage in logging.
         * @return The name.
         */
        std::string getName() const;

        void renderEntities(const std::vector<EntityPtr>& entities, IdPtr renderableId,
                            const SDL_Rect& rectToRender, SharedManagerPtr shared);
    };
}

#endif // FRTS_DRAWER_H
