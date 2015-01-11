#include "HarvestCommandBuilder.h"

#include "HarvestCommand.h"


frts::HarvestCommandBuilder::HarvestCommandBuilder(IdPtr commandType)
    : commandType{commandType}
{

}

frts::HarvestCommandBuilder::~HarvestCommandBuilder()
{

}

frts::CommandPtr frts::HarvestCommandBuilder::build(SharedManagerPtr)
{
    return makeHarvestCommand(commandType, node);
}

void frts::HarvestCommandBuilder::setSettings(ConfigNodePtr node)
{
    assert(node != nullptr);

    this->node = node;
}
