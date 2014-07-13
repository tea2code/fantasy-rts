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
        virtual void ~Renderable() {}

        /**
         * @brief Get the ID of the sprite to use.
         * @return The ID.
         */
        virtual IdPtr getSprite() const = 0;

        /**
         * @brief Get the index of the sprite. Default 0 but may change if sprite
         *        has multiple attribute.
         * @return The index.
         */
        virtual int getSpriteIndex() const = 0;

        /**
         * @brief Set the ID of the sprite to use.
         * @param id The ID.
         */
        virtual void setSprite(IdPtr id) = 0;

        /**
         * @brief Set the index of the sprite.
         * @param index The index.
         */
        virtual void setSpriteIndex(int index) = 0;
    };
}

#endif // FRTS_RENDERABLE_H
