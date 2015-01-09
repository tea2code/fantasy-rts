#include "SelectCommandBuilder.h"

#include "SelectCommand.h"


frts::SelectCommandBuilder::SelectCommandBuilder(IdPtr commandType)
    : commandType{commandType}
{

}

frts::SelectCommandBuilder::~SelectCommandBuilder()
{

}

frts::CommandPtr frts::SelectCommandBuilder::build(SharedManagerPtr)
{
    return makeSelectCommand(commandType);
}
