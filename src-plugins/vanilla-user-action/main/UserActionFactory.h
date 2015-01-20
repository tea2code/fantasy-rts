#ifndef FRTS_USERACTIONFACTORY
#define FRTS_USERACTIONFACTORY

#include <frts/module>
#include <frts/vanillamodel>

#include <memory>


namespace frts
{
    class UserActionFactory;

    /**
     * @brief Pointer to UserActionFactory.
     */
    using UserActionFactoryPtr = std::shared_ptr<UserActionFactory>;

    /**
     * @brief The user action factory creates all user actions and makes a couple of useful helper
     *        methods available for use.
     */
    class UserActionFactory : public Utility
    {
    public:
        /**
         * @brief Represents the resulting state of an execution of moveEntity().
         */
        enum class MoveEntityState
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
         * @brief Represents the result of moveEntity().
         */
        struct MoveEntityResult
        {
            /**
             * @brief The move time if state was "Moved".
             */
            Frame::time nextMoveTime;

            /**
             * @brief The result state.
             */
            MoveEntityState state;
        };

    public:
        /**
         * @brief Create drops for given entity. Won't remove or destroy this entity.
         * @param entity The entity.
         * @param pos The position where the drops should appear.
         * @param shared The shared manager.
         */
        virtual void createDrops(const EntityPtr& entity, const PointPtr& pos,
                                 const SharedManagerPtr& shared) = 0;

        /**
         * @brief Check if all the jobs (found by their markers) at a certain position are valid else
         *        stop them.
         * @param pos The position.
         * @param shared The shared manager.
         */
        virtual void confirmJobsValidOrStop(const PointPtr& pos, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Finds a path for the given entity to the job. Will set movable.
         * @param entity The entity which should execute the job.
         * @param jobPos The position of the job.
         * @param toNeighbor If true the path will go to a free neighbor of the job position else to the job position.
         * @param shared The shared manager.
         * @return True if path found else false.
         */
        virtual bool findPathToJob(const EntityPtr& entity, const PointPtr& jobPos, bool toNeighbor,
                                   const SharedManagerPtr& shared) = 0;

        /**
         * @brief Moves the entity to the next position if it has currently a path.
         * @param entity The entity.
         * @param shared The shared manager.
         * @return The result.
         */
        virtual MoveEntityResult moveEntity(const EntityPtr& entity, const SharedManagerPtr& shared) = 0;
    };
}

#endif // FRTS_USERACTIONFACTORY

