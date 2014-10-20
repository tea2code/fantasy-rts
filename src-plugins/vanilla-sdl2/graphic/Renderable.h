#ifndef FRTS_RENDERABLE_H
#define FRTS_RENDERABLE_H

#include <frts/vanillamodel>

#include <memory>


namespace frts
{
    class Renderable;

    /**
     * @brief Pointer to Renderable.
     */
    using RenderablePtr = std::shared_ptr<Renderable>;

    /**
     * @brief Component describing if a entity is renderable and specifying how.
     */
    class Renderable : public Component
    {
    public:
        virtual ~Renderable() {}

        /**
         * @brief Default ID string for component type.
         * @return The ID string.
         */
        static std::string componentType()
        {
            return "frts.vanillasdl2.graphic.renderable";
        }

        /**
         * @brief Add sprite to renderable.
         * @param id The ID.
         */
        virtual void addSprite(IdPtr id) = 0;

        /**
         * @brief Get current number of sprites in this renderable.
         * @return Number of sprites.
         */
        virtual int getNumSprites() const = 0;

        /**
         * @brief Get the ID of the sprite to use.
         * @return The ID.
         */
        virtual IdPtr getSprite(int spriteIndex) const = 0;

        /**
         * @brief Get the index of the sprite. Default 0 but may change if sprite
         *        has multiple attribute.
         * @return The index.
         */
        virtual int getSpriteIndex() const = 0;

        /**
         * @brief Set the index of the sprite.
         * @param index The index.
         */
        virtual void setSpriteIndex(int index) = 0;
    };
}

#endif // FRTS_RENDERABLE_H
