#ifndef FRTS_JOB
#define FRTS_JOB

#include <frts/shared>

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
         * @brief Result of job methods. Handled by jobs manager.
         *        Cancel: Indicates that this action wants to cancel its execution.
         *        Finished: Indicates that execution is complete.
         *        Running: Indicates that more executions are necessary to complete.
         */
        enum class State
        {
            Cancel,
            Finished,
            Running
        };

    public:
        virtual ~Job() {}

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
         * @brief The entity type for which this job is.
         * @return The entity type.
         */
        virtual IdPtr getEntityType() const = 0;

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

