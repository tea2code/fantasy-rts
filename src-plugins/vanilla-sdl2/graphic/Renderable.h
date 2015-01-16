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
         * @brief Indicates if a renderable is stackable.
         * @return True if stacking should be done else false.
         */
        virtual bool doStacking() const = 0;

        /**
         * @brief Get the ID of the sprite to use.
         * @return The ID.
         */
        virtual IdPtr getSprite() const = 0;

        /**
         * @brief Get the index of the sprite. Default is 0.
         * @return The index.
         */
        virtual unsigned int getSpriteIndex() const = 0;

        /**
         * @brief Get the number of visible levels below. Default is 0.
         * @return The transparencey.
         */
        virtual unsigned int getTransparency() const = 0;

        /**
         * @brief Indicates if sprite index was set.
         * @return True if sprite index was set.
         */
        virtual bool isSpriteIndexSet() const = 0;

        /**
         * @brief Set the ID of the sprite to use.
         * @param id The ID.
         */
        virtual void setSprite(const IdPtr& id) = 0;

        /**
         * @brief Set the index of the sprite.
         * @param index The index.
         */
        virtual void setSpriteIndex(unsigned int index) = 0;

        /**
         * @brief Set if stacking should be done.
         * @param stacking Should stacking be done.
         */
        virtual void setStacking(bool stacking) = 0;

        /**
         * @brief Set the number of visible levels below.
         * @param transparency The transparency.
         */
        virtual void setTransparency(unsigned int transparency) = 0;
    };
}

#endif // FRTS_RENDERABLE_H
