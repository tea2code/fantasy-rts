#ifndef FRTS_SPRITEPOINT_H
#define FRTS_SPRITEPOINT_H


namespace frts
{
    /**
     * @brief A sprite point descripes the position of an sprite in an image.
     */
    class SpritePoint
    {
    public:
        /**
         * @param x The x-coordinate.
         * @param y The y-coordinate.
         * @param chance The chance that this particular sprite point is selected.
         */
        SpritePoint(int x, int y, double chance = 1.0);

        /**
         * @brief The chance that this particular sprite point is selected.
         * @return The chance.
         */
        double getChance() const;

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
        int x;
        int y;
    };
}

#endif // FRTS_SPRITEPOINT_H
