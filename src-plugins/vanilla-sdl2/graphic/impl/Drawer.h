#ifndef FRTS_DRAWER_H
#define FRTS_DRAWER_H

#include <graphic/GraphicData.h>
#include <graphic/impl/SpriteManager.h>
#include <frts/shared>
#include <frts/vanillamodel>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

    class Drawer;

    /**
     * @brief Pointer to Drawer.
     */
    using DrawerPtr = std::shared_ptr<Drawer>;

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
          void operator()(TTF_Font *p) const { TTF_CloseFont(p); }
        };

        /**
         * @brief Pointer to SDL renderer.
         */
        using RendererPtr = std::shared_ptr<SDL_Renderer>;

        /**
         * @brief Pointer to SDL texture.
         */
        using TexturePtr = std::shared_ptr<SDL_Texture>;

        /**
         * @brief Pointer to SDL window.
         */
        using WindowPtr = std::unique_ptr<SDL_Window, Sdl2Deleter>;

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
        void init(const SharedManagerPtr& shared);

        /**
         * @brief Render given entities.
         * @param entities The entities.
         * @param renderableId The renderable id.
         * @param rectToRender The rectangle to render.
         * @param stacked Reference to a list of already stacked sprite ids.
         * @param shared The shared manager.
         */
        void renderEntities(const EntityVector& entities, const IdPtr& renderableId,
                            const SDL_Rect& rectToRender, IdUnorderedSet &stacked,
                            const SharedManagerPtr& shared, double zoom);

        /**
         * @brief After updating positions call this function to start the rendering.
         * @param shared The shared manager.
         */
        void renderNow(const SharedManagerPtr& shared);

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
        void setImageConfig(const SharedManagerPtr& shared, const std::string& rootNamespace, const ConfigNodePtr& imagesNode);

        /**
         * @brief Set configuration for sprites. Can be called multiple times to override
         *        existing config or add sprites.
         * @throw InvalidSpriteConfigError if sprite node represents a invalid config.
         * @param shared The shared manager.
         * @param rootNamespace The root namespace of sprites.
         * @param spritesNode The config node.
         */
        void setSpriteConfig(const SharedManagerPtr& shared, const std::string& rootNamespace, const ConfigNodePtr& spritesNode);

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
        void updateMap(const SharedManagerPtr& shared, Point::value zLevel,
                       const RegionManagerPtr& regionManager, const ModelFactoryPtr& modelFactory,
                       const GraphicDataPtr& graphicData, const ModelDataPtr& modelData);

        /**
         * @brief Update given position.
         * @param shared The shared manager.
         * @param pos The position.
         * @param zLevel The reference z-level.
         * @param regionManager The region manager.
         * @param modelFactory The model factory.
         * @param graphicData The graphic data.
         */
        void updatePosition(const SharedManagerPtr& shared, PointPtr pos, Point::value zLevel,
                            const RegionManagerPtr& regionManager, const ModelFactoryPtr& modelFactory,
                            const GraphicDataPtr& graphicData, const ModelDataPtr& modelData);

        /**
         * @brief Update all given positions.
         * @param shared The shared manager.
         * @param positions List of positions.
         * @param zLevel The reference z-level.
         * @param regionManager The region manager.
         * @param modelFactory The model factory.
         * @param graphicData The graphic data.
         */
        void updatePositions(const SharedManagerPtr& shared, const PointUnorderedSet& positions,
                             Point::value zLevel, const RegionManagerPtr& regionManager,
                             const ModelFactoryPtr& modelFactory, const GraphicDataPtr& graphicData,
                             const ModelDataPtr& modelData);

        /**
         * @brief Validate configuration. Should be called during data validation phase.
         * @throw InvalidSpriteConfigError if sprite node represents a invalid config.
         * @throw InvalidImageConfigError if image node represents a invalid config.
         * @param shared The shared manager.
         */
        void validateData(const SharedManagerPtr& shared);

    private:
        /**
         * @brief Lookup map for textures.
         */
        using TextureMap = std::unordered_map<IdPtr, TexturePtr>;

        /**
         * @brief Lookup map for image paths.
         */
        using ImageMap = std::unordered_map<IdPtr, std::string>;

    private:
        bool initialized = false;

        /**
         * @brief Sidebar width in number tiles.
         */
        Point::value sidebarWidth = 0;

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
    };

    /**
     * @brief Create new drawer.
     * @return The drawer.
     */
    inline DrawerPtr makeDrawer()
    {
         return std::make_shared<Drawer>();
    }
}

#endif // FRTS_DRAWER_H
