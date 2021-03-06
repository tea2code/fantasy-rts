#ifndef FRTS_SPRITE_H
#define FRTS_SPRITE_H

#include "SpritePoint.h"

#include <frts/shared>

#include <vector>


namespace frts
{
    /**
     * @brief Thrown if a given sprite index is out of bounds.
     */
    class SpriteIndexInvalidError : public std::runtime_error
    {
    public:
        SpriteIndexInvalidError(const std::string& msg) : std::runtime_error(msg) {}
    };

    /**
     * @brief A sprite consists of an image, its coordinates and its size. It
     *        describes the visual representation of an entity.
     */
    class Sprite
    {
    friend class SpriteManager;

    public:
        /**
         * @param image ID of the image.
         * @param height The height.
         * @param width The width.
         * @param spritePoints List of sprite points.
         */
        Sprite(const IdPtr& image, int height, int width, const std::vector<SpritePoint>& spritePoints);

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

    protected:
        /**
         * @brief Get sprite points.
         * @return List of sprite points.
         */
        std::vector<SpritePoint> getSpritePoints() const;

        /**
         * @brief Set current sprite point index. Will be used for getX() and getY().
         * @throw SpriteIndexInvalidError if index is out of bounds.
         * @param spritePointIndex The sprite point index.
         */
        void setSpritePointIndex(unsigned int spritePointIndex);

    private:
        int height;
        IdPtr image;
        unsigned int spritePointIndex = 0;
        std::vector<SpritePoint> spritePoints;
        int width;
    };
}

#endif // FRTS_SPRITE_H
