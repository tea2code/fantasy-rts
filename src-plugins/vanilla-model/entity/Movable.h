#ifndef FRTS_MOVABLE_H
#define FRTS_MOVABLE_H

#include <entity/Component.h>
#include <pathfinding/Path.h>
#include <region/Point.h>

#include <memory>


namespace frts
{
    class Movable;

    /**
     * @brief Pointer to Movable.
     */
    using MovablePtr = std::shared_ptr<Movable>;

    /**
     * @brief Entities using this component may move (walk, fly, swim...).
     */
    class Movable : public Component
    {
    public:
        enum class Direction
        {
            North,
            South,
            West,
            East,
            Up,
            Down
        };

    public:
        virtual ~Movable() {}

        /**
         * @brief Get the move direction of the current path
         *        part (between last and current position).
         * @return The direction.
         */
        virtual Direction getDirection() const = 0;

        /**
         * @brief Get the path.
         * @return The path.
         */
        virtual PathPtr getPath() const = 0;

        /**
         * @brief Get the next position of this path. Will update
         *        the direction and move the internal current position
         *        a step forward.
         * @return The position or null if path is complete.
         */
        virtual PointPtr getNextPathPos() = 0;

        /**
         * @brief Get the previous position of this path.
         * @return The position or null if path is at the beginning.
         */
        virtual PointPtr getPreviousPathPos() const = 0;

        /**
         * @brief Get the movement speed.
         * @return The speed in blocks per second.
         */
        virtual double getSpeed() const = 0;

        /**
         * @brief Set the path. This will reset this component.
         * @param path The path.
         */
        virtual void setPath(PathPtr path) = 0;

        /**
         * @brief Set the movement speed.
         * @param speed The speed in blocks per second.
         */
        virtual void setSpeed(double speed) = 0;
    };
}

#endif // FRTS_MOVABLE_H
