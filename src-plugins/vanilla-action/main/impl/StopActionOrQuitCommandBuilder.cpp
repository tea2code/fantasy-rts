#include "StopActionOrQuitCommandBuilder.h"

#include "StopActionOrQuitCommand.h"


frts::StopActionOrQuitCommandBuilder::StopActionOrQuitCommandBuilder(IdPtr commandType)
    : commandType{commandType}
{

}

frts::StopActionOrQuitCommandBuilder::~StopActionOrQuitCommandBuilder()
{

}

frts::CommandPtr frts::StopActionOrQuitCommandBuilder::build(SharedManagerPtr)
{
    return makeStopActionOrQuitCommand(commandType);
}
