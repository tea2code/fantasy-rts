#include "HarvestCommandBuilder.h"

#include "HarvestCommand.h"


frts::HarvestCommandBuilder::HarvestCommandBuilder(const IdPtr& commandType, const IdPtr& userActionType)
    : commandType{commandType}, userActionType{userActionType}
{

}

frts::HarvestCommandBuilder::~HarvestCommandBuilder()
{

}

frts::CommandPtr frts::HarvestCommandBuilder::build(const SharedManagerPtr&)
{
    return makeHarvestCommand(commandType, userActionType, node);
}

void frts::HarvestCommandBuilder::setSettings(const ConfigNodePtr& node)
{
    assert(node != nullptr);

    this->node = node;
}
