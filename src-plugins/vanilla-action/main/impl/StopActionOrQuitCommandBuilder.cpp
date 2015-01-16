#include "StopActionOrQuitCommandBuilder.h"

#include "StopActionOrQuitCommand.h"


frts::StopActionOrQuitCommandBuilder::StopActionOrQuitCommandBuilder(const IdPtr& commandType)
    : commandType{commandType}
{

}

frts::StopActionOrQuitCommandBuilder::~StopActionOrQuitCommandBuilder()
{

}

frts::CommandPtr frts::StopActionOrQuitCommandBuilder::build(const SharedManagerPtr&)
{
    return makeStopActionOrQuitCommand(commandType);
}
