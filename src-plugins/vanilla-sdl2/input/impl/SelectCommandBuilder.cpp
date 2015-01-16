#include "SelectCommandBuilder.h"

#include "SelectCommand.h"


frts::SelectCommandBuilder::SelectCommandBuilder(const IdPtr& commandType)
    : commandType{commandType}
{

}

frts::SelectCommandBuilder::~SelectCommandBuilder()
{

}

frts::CommandPtr frts::SelectCommandBuilder::build(const SharedManagerPtr&)
{
    return makeSelectCommand(commandType);
}
