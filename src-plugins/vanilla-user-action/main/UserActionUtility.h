#ifndef FRTS_USERACTIONUTILITY_H
#define FRTS_USERACTIONUTILITY_H

#include <frts/vanillamodel>


namespace frts
{
    /**
     * @brief Check if all the jobs (found by their markers) at a certain position are valid else
     *        stop them.
     * @param pos The position.
     * @param shared The shared manager.
     */
    void areJobsValid(const PointPtr& pos, const SharedManagerPtr& shared);

    /**
     * @brief Create drops for given entity. Won't remove or destroy this entity.
     * @param entity The entity.
     * @param pos The position where the drops should appear.
     * @param shared The shared manager.
     */
    void createDrops(const EntityPtr& entity, const PointPtr& pos, const SharedManagerPtr& shared);

    /**
     * @brief Finds a path for the given entity to the job. Will set movable.
     * @param entity The entity which should execute the job.
     * @param jobPos The position of the job.
     * @param toNeighbor If true the path will go to a free neighbor of the job position else to the job position.
     * @param shared The shared manager.
     * @return True if path found else false.
     */
    bool findPathToJob(const EntityPtr& entity, const PointPtr& jobPos, bool toNeighbor, const SharedManagerPtr& shared);

    /**
     * @brief Represents the result of moveEntity().
     */
    enum class MoveEntityResult
    {
        // Entity has no movable component.
        NotMovable,

        // The entity has moved.
        Moved,

        // The entity is at the target.
        AtTarget,

        // The path is blocked. Enity hasn't moved.
        Blocked
    };

    /**
     * @brief Moves the entity to the next position if it has currently a path.
     * @param entity The entity.
     * @param nextMoveTime Will contain the time until the next move afterwards.
     * @param shared The shared manager.
     * @return The result.
     */
    MoveEntityResult moveEntity(const EntityPtr& entity, Frame::time& nextMoveTime, const SharedManagerPtr& shared);
}

#endif // FRTS_USERACTIONUTILITY_H
