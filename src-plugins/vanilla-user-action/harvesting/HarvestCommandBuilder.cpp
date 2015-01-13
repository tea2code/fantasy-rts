#include "HarvestCommandBuilder.h"

#include "HarvestCommand.h"


frts::HarvestCommandBuilder::HarvestCommandBuilder(IdPtr commandType, IdPtr userActionType)
    : commandType{commandType}, userActionType{userActionType}
{

}

frts::HarvestCommandBuilder::~HarvestCommandBuilder()
{

}

frts::CommandPtr frts::HarvestCommandBuilder::build(SharedManagerPtr)
{
    return makeHarvestCommand(commandType, userActionType, node);
}

void frts::HarvestCommandBuilder::setSettings(ConfigNodePtr node)
{
    assert(node != nullptr);

    this->node = node;
}
