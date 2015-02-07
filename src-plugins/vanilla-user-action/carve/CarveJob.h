#ifndef FRTS_CARVEJOB_H
#define FRTS_CARVEJOB_H

#include <main/BaseJob.h>


namespace frts
{
    class CarveJob : public BaseJob
    {
    public:
        /**
         * @param id The job id.
         * @param type The job type.
         * @param carveEntities List of entities to carve.
         * @param doDrop If true create drop from harvested entity.
         * @param fromAbove Indicates if this action can be executed from the z-level above.
         * @param toHarvest The entity which should be harvested.
         * @param jobRequirements List of requirements for the entity which might execute the job.
         * @param jobMarker The job marker entity. Will be removed after completion.
         */
        CarveJob(const IdPtr& id, const IdPtr& type, const IdUnorderedSet& carveEntities,
                 bool doDrop, bool fromAbove, const EntityPtr& toHarvest,
                 const IdUnorderedSet& jobRequirements, const EntityPtr& jobMarker);
        ~CarveJob();

        bool checkSpecialRequirements(const EntityPtr& entity, const SharedManagerPtr& shared) const override;
        State execute(const SharedManagerPtr& shared) override;
        bool isValid(const SharedManagerPtr& shared) const override;
        State stop(const SharedManagerPtr& shared) override;

    private:
        /**
         * @brief Internal state of job.
         */
        enum class JobState
        {
            FirstExecution,
            Goto,
            Carve,
            Finished,
            Stopped
        };

    private:
        const std::string name = "frts::CarveJob";

        JobState jobState = JobState::FirstExecution;

        IdUnorderedSet carveEntities;
        bool doDrop;
        bool fromAbove;
        EntityPtr toHarvest;
    };

    /**
     * @brief Create new CarveJob.
     * @param id The job id.
     * @param type The job type.
     * @param carveEntities List of entities to carve.
     * @param doDrop If true create drop from harvested entity.
     * @param fromAbove Indicates if this action can be executed from the z-level above.
     * @param toHarvest The entity which should be harvested.
     * @param jobRequirements List of requirements for the entity which might execute the job.
     * @param jobMarker The job marker entity. Will be removed after completion.
     * @return The job.
     */
    inline JobPtr makeCarveJob(const IdPtr& id, const IdPtr& type, const IdUnorderedSet& carveEntities,
                               bool doDrop, bool fromAbove, const EntityPtr& toHarvest,
                               const IdUnorderedSet& jobRequirements, const EntityPtr& jobMarker)
    {
        assert(id != nullptr);
        assert(type != nullptr);
        assert(toHarvest != nullptr);
        assert(jobMarker != nullptr);

        return std::make_shared<CarveJob>(id, type, carveEntities, doDrop, fromAbove, toHarvest,
                                          jobRequirements, jobMarker);
    }
}

#endif // FRTS_CARVEJOB_H
