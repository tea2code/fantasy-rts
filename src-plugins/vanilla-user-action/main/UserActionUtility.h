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
    void areJobsValid(PointPtr pos, SharedManagerPtr shared);

    /**
     * @brief Create drops for given entity. Won't remove or destroy this entity.
     * @param entity The entity.
     * @param pos The position where the drops should appear.
     * @param shared The shared manager.
     */
    void createDrops(EntityPtr entity, PointPtr pos, SharedManagerPtr shared);

    /**
     * @brief Finds a path for the given entity to the job. Will set movable.
     * @param entity The entity which should execute the job.
     * @param jobPos The position of the job.
     * @param toNeighbor If true the path will go to a free neighbor of the job position else to the job position.
     * @param shared The shared manager.
     * @return True if path found else false.
     */
    bool findPathToJob(EntityPtr entity, PointPtr jobPos, bool toNeighbor, SharedManagerPtr shared);

    /**
     * @brief Moves the entity to the next position if it has currently a path.
     * @param entity The entity.
     * @param nextMoveTime Will contain the time until the next move afterwards.
     * @param shared The shared manager.
     * @return True if entity was moved else false. False indicates there is no movable component or
     *         entity is already at the target.
     */
    bool moveEntity(EntityPtr entity, Frame::time& nextMoveTime, SharedManagerPtr shared);
}

#endif // FRTS_USERACTIONUTILITY_H
