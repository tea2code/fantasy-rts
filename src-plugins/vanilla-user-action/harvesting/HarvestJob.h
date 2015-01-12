#ifndef FRTS_HARVESTJOB_H
#define FRTS_HARVESTJOB_H

#include <frts/vanillajob>


namespace frts
{
    class HarvestJob : public Job
    {
    public:
        /**
         * @param toHarvest The entity which should be harvested.
         * @param jobRequirements List of requirements for the entity which might execute the job.
         * @param jobMarker The job marker entity. Will be removed after completion.
         */
        HarvestJob(EntityPtr toHarvest, IdUnorderedSet jobRequirements, EntityPtr jobMarker);
        ~HarvestJob();

        bool checkSpecialRequirements(EntityPtr entity, SharedManagerPtr shared) const override;
        State execute(SharedManagerPtr shared) override;
        Frame::time getDueTime() const override;
        EntityPtr getExecutingEntity() const override;
        IdUnorderedSet getRequirements() const override;
        void setExecutingEntity(EntityPtr entity) override;
        State stop(SharedManagerPtr shared) override;

    private:
        /**
         * @brief Internal state of harvest job.
         */
        enum class HarvestJobState
        {
            FirstExecution,
            Goto,
            Harvest,
            Finished,
            Stopped
        };

    private:
        const std::string name = "frts::HarvestJob";

        HarvestJobState harvestState = HarvestJobState::FirstExecution;

        EntityPtr executingEntity;
        IdUnorderedSet jobRequirements;
        EntityPtr toHarvest;

        /**
         * @warning Must be set to null after removale from region to prevent possible memory leak.
         */
        EntityPtr jobMarker;

    private:
        void clearJobMarker(SharedManagerPtr shared);
    };

    /**
     * @brief Create new HarvestJob.
     * @param toHarvest The entity which should be harvested.
     * @param jobRequirements List of requirements for the entity which might execute the job.
     * @param jobMarker The job marker entity. Will be removed after completion.
     * @return The job.
     */
    inline JobPtr makeHarvestJob(EntityPtr toHarvest, IdUnorderedSet jobRequirements, EntityPtr jobMarker)
    {
        return std::make_shared<HarvestJob>(toHarvest, jobRequirements, jobMarker);
    }
}

#endif // FRTS_HARVESTJOB_H
