#ifndef FRTS_SPRITE_H
#define FRTS_SPRITE_H

#include <frts/shared>

#include <memory>


namespace frts
{
    class Sprite;

    /**
     * @brief Pointer to Sprite.
     */
    using SpritePtr = std::shared_ptr<Sprite>;

    /**
     * @brief A sprite consists of an image, its coordinates and its size. It
     *        describes the visual representation of an entity.
     */
    class Sprite
    {
    public:
        /**
         * @param image ID of the image.
         * @param height The height.
         * @param width The width.
         * @param x The x-coordinate.
         * @param y The y-coordinate.
         * @param chance The chance that this sprite is selected.
         */
        Sprite(IdPtr image, int height, int width, int x, int y, double chance = 1.0);

        /**
         * @brief The chance that this sprite is selected.
         * @return The chance.
         */
        double getChance() const;

        /**
         * @brief The height.
         * @return The height.
         */
        int getHeight() const;

        /**
         * @brief ID of the image.
         * @return ID of the image.
         */
        IdPtr getImage() const;

        /**
         * @brief The width.
         * @return The width.
         */
        int getWidth() const;

        /**
         * @brief The x-coordinate.
         * @return The x-coordinate.
         */
        int getX() const;

        /**
         * @brief The y-coordinate.
         * @return The y-coordinate.
         */
        int getY() const;

    private:
        double chance;
        int height;
        IdPtr image;
        int width;
        int x;
        int y;
    };

    /**
     * @brief Create new Sprite.
     * @param image ID of the image.
     * @param height The height.
     * @param width The width.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @param chance The chance that this sprite is selected.
     * @return The Sprite.
     */
    inline SpritePtr makeSprite(IdPtr image, int height, int width, int x, int y, double chance = 1.0)
    {
        return std::make_shared<Sprite>(image, height, width, x, y, chance);
    }
}

#endif // FRTS_SPRITE_H
