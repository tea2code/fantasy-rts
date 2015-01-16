#include "CloseContextCommandBuilder.h"

#include "CloseContextCommand.h"


frts::CloseContextCommandBuilder::CloseContextCommandBuilder(const IdPtr& commandType)
    : commandType{commandType}
{

}

frts::CloseContextCommandBuilder::~CloseContextCommandBuilder()
{

}

frts::CommandPtr frts::CloseContextCommandBuilder::build(const SharedManagerPtr&)
{
    return makeCloseContextCommand(commandType);
}
