#ifndef FRTS_JOB
#define FRTS_JOB

#include <frts/shared>
#include <frts/vanillamodel>

#include <memory>


namespace frts
{
    class Job;

    /**
     * @brief Pointer to Job.
     */
    using JobPtr = std::shared_ptr<Job>;

    /**
     * @brief Interface for jobs.
     */
    class Job
    {
    public:
        /**
         * @brief Result of job methods. Handled by jobs manager and handler.
         *        Cancel: Indicates that this action wants to cancel its execution and retry it later.
         *        Finished: Indicates that execution is complete.
         *        Running: Indicates that more executions are necessary to complete.
         *        Stop: Indicates that this job can no longer progress and shouldn't restart.
         */
        enum class State
        {
            Cancel,
            Finished,
            Running,
            Stop
        };

    public:
        virtual ~Job() {}

        /**
         * @brief Check additional requirements beside normal ones. For example are certain conditions
         *        met in the world.
         * @param entity The entity which would execute this job.
         * @param shared The shared manager.
         * @return True if special requirements are met else false.
         */
        virtual bool checkSpecialRequirements(EntityPtr entity, SharedManagerPtr shared) const = 0;

        /**
         * @brief Execute this job. Will be called when the next due time is hit and the last
         *        result was "Running".
         * @param shared The shared manager.
         * @return Current state of this execution.
         */
        virtual State execute(SharedManagerPtr shared) = 0;

        /**
         * @brief This method must return the next due time.
         * @return The due time.
         */
        virtual Frame::time getDueTime() const = 0;

        /**
         * @brief Get the entity which is currently executing this job.
         * @return The currently executing entity or null.
         */
        virtual EntityPtr getExecutingEntity() const = 0;

        /**
         * @brief Get the job id.
         * @return The job id.
         */
        virtual IdPtr getId() const = 0;

        /**
         * @brief Get a list of requirements for this job.
         * @return List of ids each representing a requirement.
         */
        virtual IdUnorderedSet getRequirements() const = 0;

        /**
         * @brief Get the job type.
         * @return The job type.
         */
        virtual IdPtr getType() const = 0;

        /**
         * @brief Indicates if this job is still valid or became obsolete.
         * @param shared The shared manager.
         * @return True if is valid else false.
         */
        virtual bool isValid(SharedManagerPtr shared) const = 0;

        /**
         * @brief Set the entity which should execute this job. Don't reset before calling stop().
         * @param entity The entity. Null is a valid value if the job is canceled.
         */
        virtual void setExecutingEntity(EntityPtr entity) = 0;

        /**
         * @brief Stop this action. Will be called when the next due time is hit and the last
         *        result was "Running".
         * @param shared The shared manager.
         * @return Current state of the stopping process.
         */
        virtual State stop(SharedManagerPtr shared) = 0;
    };
}

#endif // FRTS_JOB

