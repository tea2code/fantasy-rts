#ifndef FRTS_HARVESTACTION_H
#define FRTS_HARVESTACTION_H

#include <frts/vanillaaction>


namespace frts
{
    class HarvestAction : public Action
    {
    public:
        /**
         * @param harvestTypes List of harvestable types.
         * @param jobRequirements List of requirements for the entity which might execute the job.
         */
        HarvestAction(IdUnorderedSet harvestTypes, IdUnorderedSet jobRequirements);
        ~HarvestAction();

        State execute(SharedManagerPtr shared) override;
        State stop(SharedManagerPtr shared) override;

    private:
        const std::string name = "frts::HarvestAction";

        IdUnorderedSet harvestTypes;
        IdUnorderedSet jobRequirements;
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
