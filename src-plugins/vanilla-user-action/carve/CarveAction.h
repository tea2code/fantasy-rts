#ifndef FRTS_CARVEACTION_H
#define FRTS_CARVEACTION_H

#include <frts/vanillaaction>
#include <frts/vanillaevent>
#include <frts/vanillajob>
#include <frts/vanillamodel>


namespace frts
{
    class CarveAction : public Action, public EventObserver, public std::enable_shared_from_this<EventObserver>
    {
    public:
        /**
         * @param jobId The job id.
         * @param jobType The job type.
         * @param carveEntities List of entities to carve.
         * @param doDrop If true create drop from harvested entity.
         * @param fromAbove Indicates if this action can be executed from the z-level above.
         * @param harvestTypes List of harvestable types.
         * @param jobRequirements List of requirements for the entity which might execute the job.
         * @param jobMarker The job marker id.
         */
        CarveAction(const IdPtr& jobId, const IdPtr& jobType, const IdUnorderedSet& carveEntities,
                    bool doDrop, bool fromAbove, const IdUnorderedSet& harvestTypes,
                    const IdUnorderedSet& jobRequirements, const IdPtr& jobMarker);
        ~CarveAction();

        State execute(const SharedManagerPtr& shared) override;
        void notify(const EventPtr& event, const SharedManagerPtr& shared) override;
        State stop(const SharedManagerPtr& shared) override;

    private:
        /**
         * @brief Internal state of action.
         */
        enum class ActionState
        {
            FirstExecution,
            WaitingForSelection,
            SelectionReceived,
            Finished,
            Stopped
        };

    private:
        const std::string name = "frts::CarveAction";

        ActionState actionState = ActionState::FirstExecution;

        IdPtr jobId;
        IdPtr jobType;
        IdUnorderedSet carveEntities;
        bool doDrop;
        bool fromAbove;
        IdUnorderedSet harvestTypes;
        IdUnorderedSet jobRequirements;
        IdPtr jobMarker;

        PointVector selection;

        EntityVector jobEntities;
        std::vector<JobPtr> jobs;
    };

    /**
     * @brief Create new CarveAction.
     * @param jobId The job id.
     * @param jobType The job type.
     * @param carveEntities List of entities to carve.
     * @param doDrop If true create drop from harvested entity.
     * @param fromAbove Indicates if this action can be executed from the z-level above.
     * @param harvestTypes List of harvestable types.
     * @param jobRequirements List of requirements for the entity which might execute the job.
     * @param jobMarker The job marker id.
     * @return The action.
     */
    inline ActionPtr makeCarveAction(const IdPtr& jobId, const IdPtr& jobType, const IdUnorderedSet& carveEntities,
                                     bool doDrop, bool fromAbove, const IdUnorderedSet& harvestTypes,
                                     const IdUnorderedSet& jobRequirements, const IdPtr& jobMarker)
    {
        assert(jobId != nullptr);
        assert(jobType != nullptr);
        assert(!carveEntities.empty());
        assert(!harvestTypes.empty());
        assert(jobMarker != nullptr);

        return std::make_shared<CarveAction>(jobId, jobType, carveEntities, doDrop, harvestTypes,
                                               jobRequirements, jobMarker);
    }
}

#endif // FRTS_CARVEACTION_H
