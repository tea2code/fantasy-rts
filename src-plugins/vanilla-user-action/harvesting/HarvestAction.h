#ifndef FRTS_HARVESTACTION_H
#define FRTS_HARVESTACTION_H

#include <frts/vanillaaction>
#include <frts/vanillaevent>
#include <frts/vanillajob>
#include <frts/vanillamodel>


namespace frts
{


    class HarvestAction : public Action, public EventObserver, public std::enable_shared_from_this<EventObserver>
    {
    public:
        /**
         * @param harvestTypes List of harvestable types.
         * @param jobRequirements List of requirements for the entity which might execute the job.
         * @param jobMarker The job marker id.
         */
        HarvestAction(const IdPtr& jobId, const IdPtr& jobType, const IdUnorderedSet& harvestTypes,
                      const IdUnorderedSet& jobRequirements, const IdPtr& jobMarker);
        ~HarvestAction();

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
        const std::string name = "frts::HarvestAction";

        ActionState actionState = ActionState::FirstExecution;

        IdPtr jobId;
        IdPtr jobType;
        IdUnorderedSet harvestTypes;
        IdUnorderedSet jobRequirements;
        IdPtr jobMarker;

        PointVector selection;

        EntityVector jobEntities;
        std::vector<JobPtr> jobs;
    };

    /**
     * @brief Create new HarvestAction.
     * @param jobId The job id.
     * @param jobType The job type.
     * @param harvestTypes List of harvestable types.
     * @param jobRequirements List of requirements for the entity which might execute the job.
     * @param jobMarker The job marker id.
     * @return The action.
     */
    inline ActionPtr makeHarvestAction(const IdPtr& jobId, const IdPtr& jobType, const IdUnorderedSet& harvestTypes,
                                       const IdUnorderedSet& jobRequirements, const IdPtr& jobMarker)
    {
        assert(jobId != nullptr);
        assert(jobType != nullptr);
        assert(!harvestTypes.empty());
        assert(jobMarker != nullptr);

        return std::make_shared<HarvestAction>(jobId, jobType, harvestTypes, jobRequirements, jobMarker);
    }
}

#endif // FRTS_HARVESTACTION_H
