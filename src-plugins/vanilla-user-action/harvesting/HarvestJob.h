#ifndef FRTS_HARVESTJOB_H
#define FRTS_HARVESTJOB_H

#include <main/BaseJob.h>


namespace frts
{
    class HarvestJob : public BaseJob
    {
    public:
        /**
         * @param id The job id.
         * @param type The job type.
         * @param toHarvest The entity which should be harvested.
         * @param jobRequirements List of requirements for the entity which might execute the job.
         * @param jobMarker The job marker entity. Will be removed after completion.
         */
        HarvestJob(IdPtr id, IdPtr type, EntityPtr toHarvest, IdUnorderedSet jobRequirements, EntityPtr jobMarker);
        ~HarvestJob();

        bool checkSpecialRequirements(EntityPtr entity, SharedManagerPtr shared) const override;
        State execute(SharedManagerPtr shared) override;
        bool isValid(SharedManagerPtr shared) const override;
        State stop(SharedManagerPtr shared) override;

    private:
        /**
         * @brief Internal state of job.
         */
        enum class JobState
        {
            FirstExecution,
            Goto,
            Harvest,
            Finished,
            Stopped
        };

    private:
        const std::string name = "frts::HarvestJob";

        JobState jobState = JobState::FirstExecution;

        EntityPtr toHarvest;
    };

    /**
     * @brief Create new HarvestJob.
     * @param id The job id.
     * @param type The job type.
     * @param toHarvest The entity which should be harvested.
     * @param jobRequirements List of requirements for the entity which might execute the job.
     * @param jobMarker The job marker entity. Will be removed after completion.
     * @return The job.
     */
    inline JobPtr makeHarvestJob(IdPtr id, IdPtr type, EntityPtr toHarvest, IdUnorderedSet jobRequirements, EntityPtr jobMarker)
    {
        assert(id != nullptr);
        assert(type != nullptr);
        assert(toHarvest != nullptr);
        assert(jobMarker != nullptr);

        return std::make_shared<HarvestJob>(id, type, toHarvest, jobRequirements, jobMarker);
    }
}

#endif // FRTS_HARVESTJOB_H
