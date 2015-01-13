#ifndef FRTS_JOBMANAGERIMPL_H
#define FRTS_JOBMANAGERIMPL_H

#include <main/JobHandler.h>
#include <main/JobManager.h>

#include <list>
#include <memory>


namespace frts
{
    class JobManagerImpl : public JobManager
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

        void checkRequiredData(SharedManagerPtr shared) override;
        bool createData(SharedManagerPtr shared) override;
        std::string getName() const override;
        std::vector<std::string> getSupportedConfig() override;
        std::string getTypeName() const override;
        int getTypeVersion() const override;
        int getVersion() const override;
        bool init(SharedManagerPtr shared) override;
        bool isInitialized() const override;
        bool isPreInitialized() const override;
        void parseConfig(const std::string& key, ConfigNodePtr node, SharedManagerPtr shared) override;
        bool preInit(SharedManagerPtr shared) override;
        void validateData(SharedManagerPtr shared) override;
        void validateModules(SharedManagerPtr shared) override;

        void addJob(JobPtr job, SharedManagerPtr shared) override;
        bool employEntity(EntityPtr entity, SharedManagerPtr shared) override;
        void stopJob(JobPtr job, SharedManagerPtr shared) override;

    private:
        bool isInit = false;
        bool isPreInit = false;

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
