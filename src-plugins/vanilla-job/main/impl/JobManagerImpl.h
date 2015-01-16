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
        JobManagerImpl(const JobHandlerPtr& jobHandler);
        ~JobManagerImpl();

        /**
         * @brief The identifier.
         * @return The id string.
         */
        static std::string identifier()
        {
            return "frts/JobManager";
        }

        bool init(const SharedManagerPtr& shared) override;
        void validateModules(const SharedManagerPtr& shared) override;

        void addJob(const JobPtr& job, const SharedManagerPtr& shared) override;
        bool employEntity(const EntityPtr& entity, const SharedManagerPtr& shared) override;
        void stopJob(const JobPtr& job, const SharedManagerPtr& shared) override;

    private:
        JobHandlerPtr jobHandler;

        std::list<JobPtr> jobs;
    };

    /**
     * @brief Create new JobManager.
     * @param jobHandler The job handler.
     * @return The job manager.
     */
    inline JobManagerPtr makeJobManager(const JobHandlerPtr& jobHandler)
    {
        assert(jobHandler != nullptr);

        return std::make_shared<JobManagerImpl>(jobHandler);
    }
}

#endif // FRTS_JOBMANAGERIMPL_H
