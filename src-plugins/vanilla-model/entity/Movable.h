#ifndef FRTS_MOVABLE_H
#define FRTS_MOVABLE_H

#include <entity/Component.h>
#include <pathfinding/PathFinder.h>
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
         * @brief Get the path from start and goal (both included).
         * @return The path.
         */
        virtual PathFinder::Path getPath() const = 0;

        /**
         * @brief Get the next position of this path. Will update
         *        the direction.
         * @return The position or null if path is complete.
         */
        virtual PointPtr getNextPathPos() = 0;

        /**
         * @brief Get the previous position of this path.
         * @return The position or null if path is at the beginning.
         */
        virtual PointPtr getPreviousPathPos() const = 0;

        /**
         * @brief Set the path.
         * @param path The path.
         */
        virtual void setPath(PathFinder::Path path) = 0;
    };
}

#endif // FRTS_MOVABLE_H
