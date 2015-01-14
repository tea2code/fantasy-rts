#include "CloseContextCommandBuilder.h"

#include "CloseContextCommand.h"


frts::CloseContextCommandBuilder::CloseContextCommandBuilder(IdPtr commandType)
    : commandType{commandType}
{

}

frts::CloseContextCommandBuilder::~CloseContextCommandBuilder()
{

}

frts::CommandPtr frts::CloseContextCommandBuilder::build(SharedManagerPtr)
{
    return makeCloseContextCommand(commandType);
}
