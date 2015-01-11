#ifndef FRTS_HARVESTACTION_H
#define FRTS_HARVESTACTION_H

#include <frts/vanillaaction>
#include <frts/vanillaevent>
#include <frts/vanillamodel>


namespace frts
{


    class HarvestAction : public Action, public EventObserver, public std::enable_shared_from_this<EventObserver>
    {
    public:
        /**
         * @param harvestTypes List of harvestable types.
         * @param jobRequirements List of requirements for the entity which might execute the job.
         */
        HarvestAction(IdUnorderedSet harvestTypes, IdUnorderedSet jobRequirements);
        ~HarvestAction();

        State execute(SharedManagerPtr shared) override;
        void notify(EventPtr event, SharedManagerPtr shared) override;
        State stop(SharedManagerPtr shared) override;

    private:
        /**
         * @brief Internal state of harvest action.
         */
        enum class HarvestActionState
        {
            FirstExecution,
            WaitingForSelection,
            SelectionReceived,
            Finished,
            Stopped
        };

    private:
        const std::string name = "frts::HarvestAction";

        HarvestActionState harvestState = HarvestActionState::FirstExecution;

        IdUnorderedSet harvestTypes;
        IdUnorderedSet jobRequirements;

        PointVector selection;
    };

    /**
     * @brief Create new HarvestAction.
     * @param harvestTypes List of harvestable types.
     * @param jobRequirements List of requirements for the entity which might execute the job.
     * @return The action.
     */
    inline ActionPtr makeHarvestAction(IdUnorderedSet harvestTypes, IdUnorderedSet jobRequirements)
    {
        assert(!harvestTypes.empty());

        return std::make_shared<HarvestAction>(harvestTypes, jobRequirements);
    }
}

#endif // FRTS_HARVESTACTION_H
