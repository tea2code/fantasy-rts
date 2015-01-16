#ifndef FRTS_JOBMANAGERIMPL_H
#define FRTS_JOBMANAGERIMPL_H

#include <main/JobHandler.h>
#include <main/JobManager.h>
#include <frts/BaseUtility.h>

#include <list>
#include <memory>


namespace frts
{
    class JobManagerImpl : public BaseUtility<JobManager>
    {
    public:
        /**
         * @param jobHandler The job handler.
         */
        JobManagerImpl(JobHandlerPtr jobHandler);
        ~JobManagerImpl();

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/JobManager";
        }

        bool init(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

        void addJob(JobPtr job, SharedManagerPtr shared) override;
        bool employEntity(EntityPtr entity, SharedManagerPtr shared) override;
        void stopJob(JobPtr job, SharedManagerPtr shared) override;

    private:
        JobHandlerPtr jobHandler;

        std::list<JobPtr> jobs;
    };

    /**
     * @brief Create new JobManager.
     * @param jobHandler The job handler.
     * @return The job manager.
     */
    inline JobManagerPtr makeJobManager(JobHandlerPtr jobHandler)
    {
        assert(jobHandler != nullptr);

        return std::make_shared<JobManagerImpl>(jobHandler);
    }
}

#endif // FRTS_JOBMANAGERIMPL_H
