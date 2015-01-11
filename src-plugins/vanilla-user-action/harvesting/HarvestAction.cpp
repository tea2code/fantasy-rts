#include "HarvestAction.h"


frts::HarvestAction::HarvestAction(IdUnorderedSet harvestTypes, IdUnorderedSet jobRequirements)
    : harvestTypes{harvestTypes}, jobRequirements{jobRequirements}
{

}

frts::HarvestAction::~HarvestAction()
{

}

frts::Action::State frts::HarvestAction::execute(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    shared->getLog()->debug(name, "execute");
    // TODO
    return State::Cancel;
}

frts::Action::State frts::HarvestAction::stop(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    shared->getLog()->debug(name, "stop");
    // TODO
    return State::Cancel;
}
