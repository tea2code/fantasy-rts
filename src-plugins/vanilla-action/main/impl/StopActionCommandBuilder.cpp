#include "StopActionCommandBuilder.h"

#include "StopActionCommand.h"


frts::StopActionCommandBuilder::StopActionCommandBuilder(const IdPtr& commandType)
    : commandType{commandType}
{

}

frts::StopActionCommandBuilder::~StopActionCommandBuilder()
{

}

frts::CommandPtr frts::StopActionCommandBuilder::build(const SharedManagerPtr&)
{
    return makeStopActionCommand(commandType);
}
