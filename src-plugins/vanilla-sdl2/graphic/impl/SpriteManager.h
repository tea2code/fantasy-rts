#ifndef FRTS_SPRITEMANAGER_H
#define FRTS_SPRITEMANAGER_H

#include "Sprite.h"
#include <graphic/Renderable.h>

#include <frts/configuration>
#include <frts/shared>

#include <string>
#include <unordered_map>


namespace frts
{
    /**
     * @brief Thrown if the sprite config is invalid.
     */
    class InvalidSpriteConfigError : public DataViolation
    {
    public:
        InvalidSpriteConfigError(const std::string& msg) : DataViolation(msg) {}
    };

    /**
     * @brief The sprite manager controls all sprites and offers
     *        access to them.
     */
    class SpriteManager
    {
    public:
        SpriteManager();

        /**
         * @brief Select the correct sprite for the given renderable.
         * @param renderable The renderable.
         * @return The selected sprite.
         */
        Sprite getSprite(RenderablePtr renderable);

        /**
         * @brief Set configuration for sprites. Can be called multiple times to override
         *        existing config or add sprites.
         * @throw InvalidSpriteConfigError if sprite node represents a invalid config.
         * @param shared The shared manager.
         * @param rootNamespace The root namespace of sprites.
         * @param spritesNode The config node.
         */
        void setConfig(SharedManagerPtr shared, const std::string& rootNamespace, ConfigNodePtr spritesNode);

        /**
         * @brief Validate configuration. Should be called during data validation phase.
         * @throw InvalidSpriteConfigError if sprite node represents a invalid config.
         * @param shared The shared manager.
         */
        void validateData(SharedManagerPtr shared);

    private:
        /**
         * @brief Lookup map for sprites.
         */
        using SpriteMap = std::unordered_map<IdPtr, Sprite, IdHash, IdEqual>;

    private:
        IdPtr fallback;
        bool isConfigInitialized;
        SpriteMap sprites;
    };
}

#endif // FRTS_SPRITEMANAGER_H
