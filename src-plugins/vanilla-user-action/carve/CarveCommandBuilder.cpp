#include "CarveCommandBuilder.h"

#include "CarveCommand.h"


frts::CarveCommandBuilder::CarveCommandBuilder(const IdPtr& commandType, const IdPtr& userActionType)
    : commandType{commandType}, userActionType{userActionType}
{

}

frts::CarveCommandBuilder::~CarveCommandBuilder()
{

}

frts::CommandPtr frts::CarveCommandBuilder::build(const SharedManagerPtr&)
{
    return makeCarveCommand(commandType, userActionType, node);
}

void frts::CarveCommandBuilder::setSettings(const ConfigNodePtr& node)
{
    assert(node != nullptr);

    this->node = node;
}
