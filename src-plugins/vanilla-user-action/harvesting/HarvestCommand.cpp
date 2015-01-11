#include "HarvestCommand.h"


frts::HarvestCommand::HarvestCommand(IdPtr commandType, ConfigNodePtr settings)
    : commandType{commandType}
{
    // TODO
}

frts::HarvestCommand::~HarvestCommand()
{

}

void frts::HarvestCommand::execute(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    shared->getLog()->debug(name, "execute");

    // TODO
}

frts::IdPtr frts::HarvestCommand::getCommandType() const
{
    return commandType;
}

void frts::HarvestCommand::undo(SharedManagerPtr shared)
{
    assert(shared != nullptr);

    shared->getLog()->debug(name, "undo");

    // TODO
}
