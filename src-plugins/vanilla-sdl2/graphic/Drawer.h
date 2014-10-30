#ifndef FRTS_DRAWER_H
#define FRTS_DRAWER_H

#include <graphic/impl/SpriteManager.h>

#include <frts/vanillamodel>

#include <SDL2/SDL.h>

#include <frts/shared>

#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>


namespace frts
{
    /**
     * @brief Thrown if the image config is invalid.
     */
    class InvalidImageConfigError : public std::runtime_error
    {
    public:
        InvalidImageConfigError(const std::string& msg) : std::runtime_error(msg) {}
    };

    /**
     * @brief The drawer updates the screen and paints everything.
     */
    class Drawer
    {
    public:
        Drawer();
        ~Drawer();

        /**
         * @brief Initialize drawer. Any configuration must be set before.
         * @param shared The shared manager.
         */
        void init(SharedManagerPtr shared);

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
         * @brief Set configuration for sprites. Can be called multiple times to override
         *        existing config or add sprites.
         * @throw InvalidSpriteConfigError if sprite node represents a invalid config.
         * @param shared The shared manager.
         * @param rootNamespace The root namespace of sprites.
         * @param spritesNode The config node.
         */
        void setSpriteConfig(SharedManagerPtr shared, const std::string& rootNamespace, ConfigNodePtr spritesNode);

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

        /**
         * @brief Validate configuration. Should be called during data validation phase.
         * @throw InvalidSpriteConfigError if sprite node represents a invalid config.
         * @throw InvalidImageConfigError if image node represents a invalid config.
         * @param shared The shared manager.
         */
        void validateData(SharedManagerPtr shared);

    private:
        /**
         * @brief Deleter for std::unique_ptr for SDL.
         * @see http://stackoverflow.com/a/24252225
         */
        struct Sdl2Deleter
        {
          void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
          void operator()(SDL_Renderer *p) const { SDL_DestroyRenderer(p); }
          void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
        };

    private:
        /**
         * @brief Pointer to SDL renderer.
         */
        using RendererPtr = std::unique_ptr<SDL_Renderer, Sdl2Deleter>;

        /**
         * @brief Pointer to SDL texture.
         */
        using TexturePtr = std::unique_ptr<SDL_Texture, Sdl2Deleter>;

        /**
         * @brief Pointer to SDL window.
         */
        using WindowPtr = std::unique_ptr<SDL_Window, Sdl2Deleter>;

        /**
         * @brief Lookup map for textures.
         */
        using TextureMap = std::unordered_map<IdPtr, TexturePtr, IdHash, IdEqual>;

    private:
        bool initialized;

        Point::value offsetX;
        Point::value offsetY;

        Point::value screenHeight;
        Point::value screenWidth;

        int tileHeight;
        int tileWidth;

        RendererPtr renderer;
        TextureMap textures;
        WindowPtr window;

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
