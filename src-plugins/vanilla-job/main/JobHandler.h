#ifndef FRTS_JOBHANDLER_H
#define FRTS_JOBHANDLER_H

#include "Job.h"

#include <frts/BaseTickable.h>

#include <queue>
#include <unordered_set>
#include <utility>


namespace frts
{
    class JobHandler;

    /**
     * @brief Pointer to JobHandler.
     */
    using JobHandlerPtr = std::shared_ptr<JobHandler>;

    /**
     * @brief The job handlers runs the currently active jobs and allows to stop them.
     *        The job handler will send an event if a job has finished/stopped.
     */
    class JobHandler : public BaseTickable
    {
    public:
        JobHandler();
        ~JobHandler();

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/JobHandler";
        }

        void tick(SharedManagerPtr shared) override;

        /**
         * @brief Run given job.
         * @param job The job to run.
         */
        void runJob(JobPtr job);

        /**
         * @brief Stop given job if already running.
         * @param job The job to stop.
         */
        void stopJob(JobPtr job);

    private:
        using TimeJob = std::pair<Frame::time, JobPtr>;
        using JobSet = std::unordered_set<JobPtr>;
        using JobQueue = std::priority_queue<TimeJob, std::vector<TimeJob>, std::greater<TimeJob>>;

    private:
        JobSet knownJobs;
        JobQueue runningJobs;
        JobQueue stoppingJobs;
        JobSet toStop;
    };

    /**
     * @brief Create a new job handler.
     * @return The job handler.
     */
    inline JobHandlerPtr makeJobHandler()
    {
        return std::make_shared<JobHandler>();
    }
}

#endif // FRTS_JOBHANDLER_H
