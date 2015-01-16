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
         * @param shared The shared manager.
         */
        virtual void addJob(const JobPtr& job, const SharedManagerPtr& shared) = 0;

        /**
         * @brief If possible employ given entity.
         * @param entity The entity.
         * @param shared The shared manager.
         * @return True if entity was employed else false.
         */
        virtual bool employEntity(const EntityPtr& entity, const SharedManagerPtr& shared) = 0;

        /**
         * @brief Stop job.
         * @param job The job.
         * @param shared The shared manager.
         */
        virtual void stopJob(const JobPtr& job, const SharedManagerPtr& shared) = 0;
    };
}

#endif // FRTS_JOBMANAGER
