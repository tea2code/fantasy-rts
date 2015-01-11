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
         */
        HarvestJob(EntityPtr toHarvest, IdUnorderedSet jobRequirements);
        ~HarvestJob();

        bool checkSpecialRequirements(EntityPtr entity, SharedManagerPtr shared) const override;
        State execute(SharedManagerPtr shared) override;
        Frame::time getDueTime() const override;
        EntityPtr getExecutingEntity() const override;
        IdUnorderedSet getRequirements() const override;
        void setExecutingEntity(EntityPtr entity) override;
        State stop(SharedManagerPtr shared) override;

    private:
        EntityPtr executingEntity;
        IdUnorderedSet jobRequirements;
        EntityPtr toHarvest;
    };

    /**
     * @brief Create new HarvestJob.
     * @param toHarvest The entity which should be harvested.
     * @param jobRequirements List of requirements for the entity which might execute the job.
     * @return The job.
     */
    inline JobPtr makeHarvestJob(EntityPtr toHarvest, IdUnorderedSet jobRequirements)
    {
        return std::make_shared<HarvestJob>(toHarvest, jobRequirements);
    }
}

#endif // FRTS_HARVESTJOB_H
