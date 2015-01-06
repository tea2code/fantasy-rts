#ifndef FRTS_JOBMANAGER
#define FRTS_JOBMANAGER

#include "Job.h"

#include <frts/module>
#include <frts/shared>

#include <memory>


namespace frts
{
    class JobManager;

    /**
     * @brief Pointer to JobManager.
     */
    using JobManagerPtr = std::shared_ptr<JobManager>;

    /**
     * @brief The job manager has a list of not yet started jobs and forwards them to the
     *        job handler if a adequate entity is provided.
     */
    class JobManager : public Utility
    {
    public:
        virtual ~JobManager() {}

        /**
         * @brief Add a new job.
         * @param job The job.
         */
        virtual void addJob(JobPtr job) = 0;

        /**
         * @brief If possible employ given entity.
         * @param entity The entity.
         * @return True if entity was employed else false.
         */
        virtual bool employEntity(EntityPtr entity) = 0;

        /**
         * @brief Stop job.
         * @param job The job.
         */
        virtual void stopJob(JobPtr job) = 0;
    };
}

#endif // FRTS_JOBMANAGER
