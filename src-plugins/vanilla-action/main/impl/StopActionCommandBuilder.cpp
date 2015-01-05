#include "StopActionCommandBuilder.h"

#include "StopActionCommand.h"


frts::StopActionCommandBuilder::StopActionCommandBuilder(IdPtr commandType)
    : commandType{commandType}
{

}

frts::StopActionCommandBuilder::~StopActionCommandBuilder()
{

}

frts::CommandPtr frts::StopActionCommandBuilder::build(SharedManagerPtr)
{
    return makeStopActionCommand(commandType);
}
